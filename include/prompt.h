#ifndef PROMPT_H
#define PROMPT_H
#include "init.h"

typedef struct prompt {
    unsigned char hostname;
    unsigned char username;
    unsigned char prompt; //the prompt string to display
    unsigned char INPUT_USR[INPUT_BUFFER_SIZE]; //buffer to store the user input
    char priority; //define the prompt character if is root or not; 1=not root
    char prompt_item; //define the prompt caracter
    int  prompt_file_fd; //file descriptor of the prompt
}PROMPT;

extern PROMPT * prompt;

int set_prompt (void);


#endif