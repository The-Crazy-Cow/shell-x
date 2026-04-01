#ifndef SH_KERN_H
#define SH_KERN_H


//define the streams components 
#define INPUT_BUFFER_SIZE 0x400
#define OUTPUT_BUFFER_SIZE 0x400


//the tty struct  incoreporated all systems datas and variables
typedef struct TTY_STRUCT {
    char * prompt;
}TTY_STRUCT;


int init (void);
int system_call (char * cmd);
int init_user_info(void);


#endif // SH_KERN_H