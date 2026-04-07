#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>

#ifdef DEBUG

//LOGS DESTINATION HANDLE
#ifndef LOG_STREAM
#define LOG_STREAM stderr
#endif

//========== L O G   L E V E L S =========
#define LOG_LEVEL_ERROR 0x01   //ERROS
#define LOG_LEVEL_WARN  0x02    //WARNINGS
#define LOG_LEVEL_INFO  0x04    //INFORMATIONELS
#define LOG_LEVEL_DEBUG 0x08    //SIMPLE DEBUGGING
//=========================================


#define pr_debug(fmt,...) \
    fprintf(LOG_STREAM,"\nin %s::%s::%d::" fmt "\n",__func__,__FILE__,__LINE__,##__VA_ARGS__) 
#else //IF DEBUG IS NOT ON  
#define pr_debug(...) ((void)0) /*nothing*/
#endif

//DEFAULT LOG LEVEL WITH DEBUG ON
#ifndef DEBUG_FLAGS
#define DEBUG_FLAGS LOG_LEVEL_INFO
#endif

#define LOG_ERROR(fmt,...)\
        do{        if (LOG_LEVEL_ERROR & DEBUG_FLAGS) pr_debug("[ERROR]::" fmt,##__VA_ARGS__);\
        }while(0)

#define LOG_WARN(fmt,...) \
        do{        if (LOG_LEVEL_WARN & DEBUG_FLAGS) pr_debug("[WARNING]::" fmt,##__VA_ARGS__);\
        }while(0)

#define LOG_INFO(fmt,...)\
        do{        if (LOG_LEVEL_INFO & DEBUG_FLAGS) pr_debug("[INFO]::" fmt,##__VA_ARGS__);\
        }while(0)

#define LOG_DEBUG(fmt,...)\
        do{        if (LOG_LEVEL_DEBUG & DEBUG_FLAGS) pr_debug("[DEBUG]::" fmt,##__VA_ARGS__);\
        }while(0)


#endif /*DEBUG_H*/