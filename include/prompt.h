#ifndef PROMPT_H
#define PROMPT_H


typedef struct prompt {
    unsigned char hostname;
    unsigned char username;
    char priority; //define the prompt character if is root or not; 1=not root
    char prompt_item; //define the prompt caracter
    int  prompt_file_fd; //file descriptor of the prompt
}PROMPT;

extern PROMPT * prompt;

#endif