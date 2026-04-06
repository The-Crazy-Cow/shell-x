/*@
*implement the core of the tty system : 
*to add new syscall add it to the functional variable syscalls define above 
*by use the macro __SYSCALL()
*/
#include "core.h"
#include "utils.h"
#include "prompt.h"

#include <string.h> 
#include <stdint.h>

const char * const syscalls [][MAX_SYSCALLS_NAME_LEN]={  
                            __SYSCALL__(init,"john")  
                            __SYSCALL__(love,"am")

                            //add your syscall here

//__SYSCALL__(END,"000)specify the end of the syscall tab
//the 0x00 is just a reference to the null pointer adress dude
__SYSCALL__(END,"0x00")
}  ;    

SYS_STRUCTURE sys={ // the system structure
    .username="foo", //delete after
    .hostname="contoso",
    .syscalls = syscalls,
    };

int init (){
    #ifdef DEBUG
        pr_debug("initialisation of the shell prog");
    #endif

    //create the database

    //initialize the username and hostname etc... variables

    //initialise the syscall

    //enter in prompt
    init_prompt(); 

    return 0;
}

/*
analyser the input of the current user if is a internal command execute it , if don't return error and set lastcallstatus on negativs
see core.h to see all values of lastcallstatus and meaning
 */
void sysanalyze(){
    //char *syscall_args = calloc(strlen(sys.prompt->io_buffer) + 1, sizeof(char)); 
    char syscall_args[452]="";
    if((sys.lastcallstatus=valid_syscall(sys.prompt->io_buffer,syscall_args))==-1){
        print("Command not found"); //TODO: emmit an SYSERROR
    }else {
        print("sucess");//delete after
        /*@
        *the ultimate system call
        @*/
        func_t syscall = (func_t)(uintptr_t) sys.syscalls[sys.lastcallstatus][0];
        sys.lastcallstatus= syscall(syscall_args);
    }
    //free(syscall_args);
}

/*
*check if the first word is known by the system
*on sucess return call immediately the function reponsible of 
*the function and return the return value of this
*/
int valid_syscall(const char * cmd_sample,char *syscall_args){
    char sample[strlen(cmd_sample)+1];
    strcpy(sample,cmd_sample);

    //get the first word in the sample seperate by space => commaned name
    char * pos = strchr(sample,' ');
    if(pos!=0){
        *pos='\0';
        strcpy(syscall_args,pos+1);//get the args of the cmdline
    }

    for(int i=0;;i++){
        //to know if this is on the end of syscall tab 
        if(strcmp(syscalls[i][1],"0x00")==0)
            return -1;
        /*@
        *compare and if all things is ok return the index of the 
        *function responsible of the syscall
        */
        if(strcmp(syscalls[i][1],sample)==0){
            return i;
        }
    }
    return -1;
}

void END (void){
    //to desgined the end of syscall tab
}

//check also the use of 
//char *filename = strrchr("/usr/local/bin/myprog", '/');
//printf("%s\n", filename + 1); // affiche "myprog"
