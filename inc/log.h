#ifndef log_h
#define log_h

#include <stdio.h>

#define LOG(text){                                                          \
    printf("[%s:%d] %s\n",__FILE__,__LINE__,text);                          \
}

#endif /* log_h */
