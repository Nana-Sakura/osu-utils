#ifndef LOG_H
#define LOG_H

#include <stdio.h>

#define LOG(text){                                                  \
    char s[100];                                                   \
    sprintf(s,"[%s:%d]%s\n",__FILE__,__LINE__,text);                \
    printf("%s",s);                                                 \
}

#endif /* INCLUDE_LOG_H */
