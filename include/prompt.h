#ifndef PROMPT_H
#define PROMPT_H

#include "utils.h"
#include "core.h"

typedef struct prompt {

    char prompt[BUFFER];
    char io_buffer[BUFFER];
}PROMPT_T;


extern PROMPT_T prompt;

void __prompt(void);
int get_prompt(char *msg,char *ret);
int print(char *msg);
int init_prompt(char *prompt_fm);


#endif