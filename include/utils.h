#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

//spécifies the format for print
#define pr_debug(fmt,...) printf("\nin %s::%s::%d::" fmt "\n",__func__,__FILE__,__LINE__,##__VA_ARGS__) //see also file,line,func,date,time,stdc


#endif //utils.h