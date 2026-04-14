#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include "debug.h"
#include <stdbool.h>

#define BUFF 1024   //buffer use for io operation,often for user i/o
#define PROMPT_LEN_MAX 128 //mex length of user prompt design
#define CMDLINE_LEN_MAX BUFF   //maximum user command line input length
#define CMD_LEN_MAX 256     //maximum command's name length
#define ARGS_LEN_MAX CMDLINE_LEN_MAX - CMD_LEN_MAX //maximum command line arguments length

//handle the io operations
struct IO_OPS_STRUCT {
    char prompt[PROMPT_LEN_MAX];
    char input_op[BUFF];    //user input operation
    char output_op[BUFF];//output operation
    char cmd[CMD_LEN_MAX];  //command name
    char args[ARGS_LEN_MAX];//cmdline args
    int  lastcmdcallstatus;

    bool prmpt_prvlg;//priviliege 
    char prmpt_prvlg_caract; //prompt[$|#]
};

#endif



