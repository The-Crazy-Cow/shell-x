#include "prompt.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

PROMPT * prompt;

/* 
    set the prompt and the tty infos which depends of it
*/
int set_prompt (void){

    if(strcmp( prompt->username, "root") == 0){
        prompt->priority = 1;
        prompt->prompt_item = '$';
    } else {
        prompt->priority = 0;
        prompt->prompt_item = '#';
    }

    sprintf(prompt->prompt, "%s@%s:~%c", prompt->username,  prompt->hostname, prompt->prompt_item);

    return 0;
}

int enter_prompt(void){
    while (1)
    {       
        //display the prompt
        printf("%s ", prompt->prompt);
        fflush(stdout);
        //wait for the user input 
        errno = 0;
        if (fgets( prompt->INPUT_USR, INPUT_BUFFER_SIZE, stdin) == NULL) {
            if (errno != 0) {
                perror("Error reading from stdin");
            }
            return EXIT_FAILURE;
        }
        char  c;
        while ((c = getchar()) != '\n' && c != EOF); //to clear the input buffer 

        prompt->INPUT_USR[strcspn(prompt->INPUT_USR, "\n")] = '\0';
        printf("%d\n", system_call(prompt->INPUT_USR)); 

        //set the return variables and env
    }


    return 0;
}