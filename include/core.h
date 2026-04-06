#ifndef CORE_H
#define CORE_H

#include "prompt.h"

#define MAX_SYSCALLS_NAME_LEN 0x0FF //maximal length of the syscalls name
#define __SYSCALL__(func_name,syscall_name) {(char *) &func_name,syscall_name},

//for to cast the char in function pointer
//cause the adress of syscalls are in char * syscall tab need to perform
//cast is cover by this type en function sysanalyse: see core.c file
typedef int (*func_t)(char *chain);

typedef struct sys_structure{
    char * hostname;
    char * username;
    PROMPT_T * prompt; //contains adress of the prompt variable so access

    int lastcallstatus;//lastcallstatus contains the status of the last command success or not : 0=success; <0 command not found ; > 0 command typing input is'nt correct 
    const char * const (*syscalls)[MAX_SYSCALLS_NAME_LEN]; //index match with the magic number of each syscalls/commands and name
}SYS_STRUCTURE;

extern SYS_STRUCTURE sys;

int init(void);
void sysanalyze();
int valid_syscall(const char * sample,char * syscall_args);
void END (void);

#endif //core.h