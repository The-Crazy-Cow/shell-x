/*/
handle internals mechanism to manage the prompt
*/

#include "core.h"
#include "prompt.h"
#include "utils.h"
#include "debug.h"

#include <stdio.h>

int init (void){
    struct  IO_OPS_STRUCT tty_io;
    bool sys=true;

    init_prmpt(&sys,"user@user",&tty_io);

    prompt(&sys,&tty_io);

    return 0;
}


int cmdcall(struct IO_OPS_STRUCT *prmpt){
    LOG_DEBUG("in cmdcall");
    return 0;


    (void) prmpt;
}