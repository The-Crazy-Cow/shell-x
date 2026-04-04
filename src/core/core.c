#include "core.h"
#include "utils.h"
#include "prompt.h"

#include <string.h> // delete after

extern PROMPT_T prompt;


int init (){
    #ifdef DEBUG
        pr_debug("initialisation of the shell prog");
    #endif

    //create the database

    //enter in prompt
    init_prompt("ui@ui"); //delete after
    print("jean");

    return 0;
}

int sysanalyze(){
    //TODO after analyze and return any user prompt
    return 1;
}

