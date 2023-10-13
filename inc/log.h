//
//  log.h
//  osu-utils
//
//  Created by Merry on 2023/9/23.
//

#ifndef log_h
#define log_h

#include <stdio.h>

#define LOG(text){                                                  \
    char s[10000];                                                  \
    sprintf(s,"[%s:%d] %s\n",__FILE__,__LINE__,text);               \
    printf("%s",s);                                                 \
}

#endif /* log_h */
