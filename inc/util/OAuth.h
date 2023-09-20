//
//  OAuth.h
//  osu-utils
//
//  Created by Merry on 2023/9/20.
//

#ifndef OAuth_h
#define OAuth_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <curl/curl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "cJSON.h"

void read_token(char* tokenstring);
void on_token_expire(void);
void get_token(int clientid,const char* clientsec);
size_t token_cb(char* buffer,size_t size,size_t nitems,void* userdata);

#endif /* OAuth_h */
