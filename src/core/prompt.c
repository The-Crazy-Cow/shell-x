/*@handle the user prompt mechanism
*by structure tty_iso init in prompt
*/

#include "prompt.h"
#include "utils.h"
#include "core.h"

#include <errno.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>


/*INIT PROMPT - init the user prompt
*should be called before prompt function
*return  0 success
*        <0 errors
*/
int init_prmpt(const bool * system_status,const char * prompt,struct IO_OPS_STRUCT * prmpt){

    if (!(system_status && prompt && prmpt)){
        return -EFAULT;
    }//prompt size check is performed in set_prompt call

    LOG_INFO("valid args");
    LOG_DEBUG("%d arg0,%s arg2",*system_status,prompt);

    if (*system_status){
        int ret;
        if((ret=set_prmpt(prmpt,prompt))!=0){//set the user prompt
            return ret;
        }
        if((ret=mkunprvlg(prmpt))!=0){//make user unpriviliged first time
            return ret;
        }
    }else{
        return -EAGAIN;
    }
    LOG_INFO("init complete");
    return 0;
}

/*@param: system_status: 1 => ON ; !=1 => OFF 
*handle the user tty prompt during the execution
exit with system_status set on 0 (OFF)
0 on success else < 0
*/
int prompt (const bool * system_status,struct IO_OPS_STRUCT * prmpt){

    if (!(system_status && prmpt)) return -EFAULT;
    LOG_DEBUG("%d arg0",(* system_status));        

    if(* system_status){
        if(prmpt->prompt[0]=='\0' || (prmpt->prmpt_prvlg_caract!='$' &&
                                      prmpt->prmpt_prvlg_caract!='#')) return -EINVAL;
        LOG_INFO("valid args,exec body");

        //system going off, system status=0=> break the loop and return success
        while (*system_status){
            int ret ; //return value
            printf("%s%c ",prmpt->prompt,prmpt->prmpt_prvlg_caract);
            fflush(stdout);
            if ((ret=input(prmpt->input_op,CMDLINE_LEN_MAX))!=0) {
                return ret;
            }

            //parse the valid input
            if((ret=parse_cmdline(prmpt->input_op,strlen(prmpt->input_op),
                                prmpt->cmd,(size_t) CMD_LEN_MAX,
                                prmpt->args,(size_t) ARGS_LEN_MAX))!=0)
            {
                LOG_ERROR("parse_cmdline %d:%s",ret,strerror(ret));
                return ret;
            }

            //call the wrapper cmdcall to handle the execution of the cmd
            prmpt->lastcmdcallstatus = cmdcall(prmpt);
        }
        //on success after excute prompt     
        LOG_DEBUG("exit: %d arg0",*system_status);        
        return 0;
    }else{
        return -EAGAIN;
    }
}

int set_prmpt(struct IO_OPS_STRUCT * prmpt,const char * prompt){
    if (!(prmpt && prompt)) return -EFAULT;

    while(isspace((unsigned char ) *prompt)) prompt++;

    if (*prompt=='\0'){
        LOG_DEBUG("empty prompt");
        return -EINVAL;
    }

    size_t prompt_len = strlen(prompt);
    if (PROMPT_LEN_MAX<prompt_len+1) return -EOVERFLOW;

    snprintf(prmpt->prompt, PROMPT_LEN_MAX, "%s", prompt);
    return 0;
}

//check the privielge coherences
int check_prvlg(struct IO_OPS_STRUCT * prmpt){
    if (prmpt==0) return -EFAULT;

    //false if coherent
    bool logic_prvlg = prmpt->prmpt_prvlg_caract!='#' && prmpt->prmpt_prvlg_caract!='$';
    bool logic_user = prmpt->prmpt_prvlg==0 && prmpt->prmpt_prvlg_caract =='#';
    bool logic_root = prmpt->prmpt_prvlg==1 && prmpt->prmpt_prvlg_caract =='$';

    if(logic_prvlg||logic_user||logic_root) return -EINVAL;
    return 0;
}


//MAKE PRIVILIGIED USER :set the priviligied user prompt
int mkprvlg (struct IO_OPS_STRUCT * prmpt){
    if (! prmpt) return -EFAULT;
    int ret =  0;
    if ((ret=check_prvlg(prmpt))!=0){
        return ret;
    }
    prmpt->prmpt_prvlg=1;
    prmpt->prmpt_prvlg_caract='#'; //root 
    return check_prvlg(prmpt);
}

//MAKE UNPRIVILIGIED USER :set the standard user prompt
int mkunprvlg   (struct IO_OPS_STRUCT * prmpt){
    if (! prmpt) return -EFAULT;
    prmpt->prmpt_prvlg=0;
    prmpt->prmpt_prvlg_caract='$'; //standard user
    return check_prvlg(prmpt);
}

//get priviligied user status
int isprvlg   (struct IO_OPS_STRUCT * prmpt){
    if (! prmpt) return -EFAULT;
    int ret = 0;
    if ((ret=check_prvlg(prmpt))!=0){
        return ret;
    }
    return (prmpt->prmpt_prvlg);
}

/*print - write on stdout
*return 0 success
        1 all data not print on stdout
       >0 error 
*/
int print(const char * buff){
    if(!buff) return -EFAULT;
    if(buff[0]=='\0') return -ENODATA;

    size_t buff_len=strlen(buff);
    int ret=0;

    errno=0;
    if((ret=write(STDOUT_FILENO,buff,buff_len))< 0){
        LOG_ERROR("failled output op - %d:%s",errno,strerror(errno));
        return -errno;
    }
    
    if((size_t)ret!=buff_len){
        LOG_WARN("data truncated on stdout");
        return 1;
    }
    LOG_INFO("sucess output op");
    return 0;
}

/*INPUT - get the user input
*/
int input(char *buff,size_t buff_size){
    if (!buff) return -EFAULT;
    if(buff_size==0) return -EINVAL;

    errno=0;
    int ret;
    if((ret=read(STDIN_FILENO,buff,buff_size-1))<0){
        LOG_ERROR("failled intput op - %d:%s",errno,strerror(errno));
        return -errno;   
    }
     if (ret == 0) {
        return -ENODATA; // EOF
    }

    buff[ret] = '\0';

    char *line_feed_pos = strchr(buff, '\n');
    if (line_feed_pos) {
        *line_feed_pos = '\0';
    } else {
        //empty stdin buffer
        char c;
        while ((c=fgetc(stdin))!='\n' && c!=EOF);
    }

    if (buff[0] == '\0') {
        LOG_WARN("No data read");
        return -ENODATA;
    }
    return 0;
}

/*parse the commandline via user_inout_size in cmd=command and args=commande args
* supply by the user
@params *._size are buffers of parse_cmdline arguments
*/
int parse_cmdline( char *user_input,const size_t user_input_size,//User_Input_size == strlen(user_input)
                 char * cmd,const size_t cmd_size, 
                 char * args,const size_t args_size){
    
    LOG_INFO("check values");
    if (! (user_input && cmd && args)) return -EFAULT;
    if(!(user_input_size && cmd_size && args_size)) return -EINVAL;
    LOG_INFO("'%s' %zu  %zu ",user_input,user_input_size,args_size);

    //Move to first no space caracter=> fetch the command name
    while(isspace((unsigned char ) *user_input)) user_input++;
    if (*user_input=='\0') return -EINVAL;//entire input was spaces caract.
    char * space_pos=user_input;

    //Move to next space, delimit command name Length
    while(!isspace((unsigned char ) * space_pos)) space_pos++;
                
     size_t cmd_len;
    //input= command without arguments
    if (*space_pos=='\0') 
        cmd_len = strlen(user_input);
    else{

        //also use cmd_len= end_ptr - start-ptr
        cmd_len = strlen(user_input) -strlen(space_pos);
    LOG_INFO("'%s' %zu  %zu ",user_input,cmd_len,cmd_size);

        //Move to next first space caracter
        while(isspace((unsigned char ) *space_pos)) space_pos++;

        //next caracter is not the end
        if(*space_pos!='\0'){//fetch arguments
            size_t args_len = strlen (space_pos);

            //args_size is not sufficient
            LOG_DEBUG("%zu::%zu",args_size,args_len);
            if (args_size < args_len +1) return -EOVERFLOW;

            strncpy(args,space_pos,ARGS_LEN_MAX);
            args[args_len]='\0';
        }
    }

    //cmd_size buffer not sufficient 
    if (cmd_size < cmd_len+1) return -EOVERFLOW;
    
    strncpy(cmd,user_input,cmd_len);
    cmd[cmd_len]='\0';

    //END
    LOG_INFO("'%s' %zu '%s' %zu ",user_input,user_input_size,args,args_size);
    return 0;
}
