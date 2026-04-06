#include "prompt.h"
#include "core.h"

#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/*
    defines fonctions to handle the prompt mechanisms, see prompt.h which define prompt variables
*/

PROMPT_T prompt;
static void __prompt (); //declares on at the bottom of the file

//init the prompt design
int init_prompt(){
    snprintf(prompt.prompt,BUFFER-1,"%s@%s$",sys.username,sys.hostname);
    sys.prompt = &prompt;
    return EXIT_SUCCESS;
}

//print on the prompt
int print(char *msg){
        #ifdef DEBUG
    pr_debug("in print");
    #endif

    if(!strlen(msg)){ //avoid to 
        perror("printing object is null");
        return EXIT_FAILURE;
    }
    if(strlen(msg)>BUFFER-1){ //see to make an log file 
        perror("msg len is too long");
        return EXIT_FAILURE;
    }
    strncpy(prompt.io_buffer, msg, strlen(msg)+1);
    prompt.io_buffer[strlen(msg)] = '\0'; //avoid strlen(prompt.io_buffer) - 1 : when strlen=0 can be an membug can use BUFF-1

    __prompt();
    return EXIT_SUCCESS;
}

//print and give to user the input access
int get_prompt(char *msg,char *ret){
          #ifdef DEBUG
    pr_debug("in print");
    #endif

    if(sizeof(ret)>BUFFER-1){ //see to make an log file 
        printf("return buffer len is too long");
        return EXIT_FAILURE;
    }

    if (!print(msg)){
        return EXIT_FAILURE;
    }
    prompt.io_buffer[0]='\0';
    __prompt();

    strncpy(ret, prompt.io_buffer, BUFFER-1);
    ret[sizeof(ret)-1] = '\0';

    return EXIT_SUCCESS;
}

//internal functions which handle low level the prompt
static void __prompt (void){
    #ifdef DEBUG
    pr_debug("in prompt");
    #endif

    errno=1;
    while (1){
        //print the prompt symbol
        printf("%s",prompt.prompt);

        //check if the io buffer contains something to print 
        if(strlen(prompt.io_buffer)!=0){
            printf("%s\n",prompt.io_buffer);
        }else{
            if(!fgets(prompt.io_buffer,BUFFER-1,stdin)){
                perror("error on stdin ");
                _exit(1);
            }
            prompt.io_buffer[strcspn(prompt.io_buffer, "\n")] = '\0'; 
            
            if(strlen(prompt.io_buffer))
                sysanalyze(); //pass the handle to the system core to analyze ans return to user ; check the sys.lastcallstatus variable in the core.h in sys structure
        }
        prompt.io_buffer[0]='\0';
    }
}

