#ifndef PROMPT_H
#define PROMPT_H

#include "utils.h"
#define BUFFER 0x400 //the default buffer for every sys' varaible

typedef struct prompt {

    char prompt[BUFFER];
    char io_buffer[BUFFER];
}PROMPT_T;


extern PROMPT_T prompt;

int get_prompt(char *msg,char *ret);
int print(char *msg);
int init_prompt();


#endif