#include "sh_kern.h"
#include <stdio.h>

/*
    by default the db file  should be in the same directory as the executable, but you can specify a different path by setting the DB_PATH environment variable. For example:
    DB_PATH=/path/to/your/database 
*/

int main (int argc, char *argv[], char *envp[]){
    #ifdef DEBUG
    printf("main function started...\n");
    #endif

    (void) argc; //to avoid unused parameter warning
    (void) argv; //to avoid unused parameter warning
    (void) envp; //to avoid unused parameter warning

    init();
    return 0;
}