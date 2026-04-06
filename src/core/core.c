#include "core.h"
#include "utils.h"
#include "prompt.h"

#include <string.h> // delete after


SYS_STRUCTURE sys;
/*
    implement the core of the tty system : 
    to add new syscall add it to the function 
*/

const char * const syscalls [][MAX_SYSCALLS_NAME_LEN]={  
                            __SYSCALL__(init,"john")  //adding the syscall



//specify the end of the syscall tab
__SYSCALL__(END,"0x00")//<= just a reference to null pointer adress dude
}  ;                     

int init (){
    #ifdef DEBUG
        pr_debug("initialisation of the shell prog");
    #endif

    //create the database


    //initialize the username and hostname etc... variables
    sys.hostname = "lae"; //delete after
    sys.username = "jd";


    //initialise the syscall
    


    //enter in prompt
    init_prompt(); 
    print("jean");

    return 0;
}


/*
analyser the input of the current user if is a internal command execute it , if don't return error and set lastcallstatus on negativs
see core.h to see all values of lastcallstatus and meaning
 */

void sysanalyze(){

//implement syscall mechanism
    if(valid_syscall(sys.prompt->io_buffer)!=1){
        print("Command not found"); //TODO: emmit an SYSERROR
    }else{
        print("sucess");
    }
}

/*
    check if the first word is known by the system
*/
int valid_syscall(const char * cmd_sample){
    char sample[strlen(cmd_sample)+1];
    strcpy(sample,cmd_sample);

    //get the first word in the sample seperate by space => commaned name
    char * pos = strchr(sample,' ');
    if(pos!=0)
        *pos='\0';

    for(int i=0;;i++){
        //to know if this is on the end of syscall tab 
        if(strcmp(syscalls[i][1],"0x00")==0)
            return -1;
        //compare
        if(strcmp(syscalls[i][1],sample)==0)
            return 1;
    }
    return -1;
}


void END (void){
    //to desgined the end of syscall tab
}

//check also the use of 
//char *filename = strrchr("/usr/local/bin/myprog", '/');
//printf("%s\n", filename + 1); // affiche "myprog"
