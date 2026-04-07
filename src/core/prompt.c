#include "prompt.h"
#include "utils.h"

#include <errno.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>



int print(char *args_line){

}

int input(char *args_line){

}

int parse_cmdline(const char *user_input,const ssize_t user_input_size,//User_Input_size == strlen(user_input)
                 char * cmd,const ssize_t cmd_size, 
                 char * args,const ssize_t args_size){
    
    LOG_INFO("check values");
    if (! (user_input && cmd && args)) return -EFAULT;
    if(!(user_input_size && cmd_size && args_size)) return -EINVAL;
    LOG_INFO("'%s' %zu '%s' %zu ",user_input,user_input_size,args,args_size);

    //Move to first no space caracter=> fetch the command name
    while(isspace((unsigned char ) *user_input)) user_input++;
    if (*user_input=='\0') return -EINVAL;//entire input was spaces caract.
    char * space_pos=user_input;

    //Move to next space, delimit command name Length
    while(!isspace((unsigned char ) * space_pos)) space_pos++;
                
     ssize_t cmd_len;
    //input= command without arguments
    if (*space_pos=='\0') 
        cmd_len = strlen(user_input);
    else{
        cmd_len = (ssize_t) (space_pos - user_input);

        //Move to next first space caracter
        while(isspace((unsigned char ) *space_pos)) space_pos++;

        //next caracter is not the end
        if(*space_pos!='\0'){//fetch arguments
            ssize_t args_len = strlen (space_pos);

            //args_size is not sufficient
            if (args_size < args_len +1) return -EOVERFLOW;

            strncpy(args,space_pos,args_len);
            args[args_len]='\0';
        }
    }

    //cmd_size buffer not sufficient 
    if (cmd_size < cmd_len+1) return -EOVERFLOW;
    
    strncpy(cmd,user_input,cmd_len);
    cmd[cmd_len]='\0';

    return 0;
}
