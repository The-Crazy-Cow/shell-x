#ifndef PROMPT_H
#define PROMPT_H

#include "core.h"
#include <unistd.h>
#include <stdbool.h>
#include "utils.h"


//=======wrapper function====================

//===========================================

int parse_cmdline(char *user_input,const size_t user_input_size,
                    char * cmd,size_t cmd_size, 
                    char * args,size_t args_size);

int input(char *buff,size_t buff_size);
int print(const char * buff);
int isprvlg   (struct IO_OPS_STRUCT * prmpt);
int mkunprvlg  (struct IO_OPS_STRUCT * prmpt);
int mkprvlg (struct IO_OPS_STRUCT * prmpt);
int check_prvlg(struct IO_OPS_STRUCT * prmpt);
int set_prmpt(struct IO_OPS_STRUCT * prmpt,const char * prompt);
int prompt (const bool * system_status,struct IO_OPS_STRUCT * prmpt);
int init_prmpt(const bool * system_status,const char * prompt,struct IO_OPS_STRUCT * prmpt);

#endif /*PROMPT_H*/