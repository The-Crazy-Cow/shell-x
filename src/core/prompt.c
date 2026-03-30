#include "prompt.h"
#include <fcntl.h>
#include <stdio.h>

PROMPT * prompt;

/* 
    get the path prompt_file to init the structure PROMPT to init the prompt 
*/
void init_prompt (unsigned char  prompt_file){
    prompt->prompt_file_fd = open((char *) prompt_file,O_RDONLY);
    if(prompt->prompt_file_fd == -1){
        //error 
    }

    //get the hostname,
    int ret;

}