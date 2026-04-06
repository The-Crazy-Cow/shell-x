#ifndef CORE_H
#define CORE_H

#include "prompt.h"

#define MAX_SYSCALLS_NAME_LEN 0x0FF
#define __SYSCALL__(func_name,syscall_name) {(char *) &func_name,syscall_name},

typedef struct sys_structure{
    char * hostname;
    char * username;
    PROMPT_T * prompt; //contains adress of the prompt variable so access

    char lastcallstatus;//lastcallstatus contains the status of the last command success or not : 0=success; <0 command not found ; > 0 command typing input is'nt correct 
    char **syscalls; //index match with the magic number of each syscalls/commands and name
}SYS_STRUCTURE;

extern SYS_STRUCTURE sys;


int init(void);
void sysanalyze();
int valid_syscall(const char * sample);
void END (void);

#endif //core.h