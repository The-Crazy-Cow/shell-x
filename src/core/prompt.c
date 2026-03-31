#include "prompt.h"
#include <fcntl.h>
#include <stdio.h>

PROMPT * prompt;

/* 
    set the prompt and the tty infos which depends of it
*/
int set_prompt (void){

    if(prompt->username != "root"){
        prompt->priority = 1;
        prompt->prompt_item = '$';
    } else {
        prompt->priority = 0;
        prompt->prompt_item = '#';
    }

    sprintf(prompt->prompt, "%s@%s:~%c", prompt->username, prompt->hostname, prompt->prompt_item);
    
    return 0;
}