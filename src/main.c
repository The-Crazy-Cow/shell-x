#include "core.h"
#include "utils.h"


int main (int argc, char *argv[],char *envp[]){
    (void) argc;
    (void) argv;
    (void) envp;

    if(init()==-1){
        pr_debug("");
        return -1;
    }
    return 0;
}