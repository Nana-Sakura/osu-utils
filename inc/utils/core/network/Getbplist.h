//
//  Getbplist.h
//  osu-utils
//
//  Created by Merry on 2023/9/20.
//

#ifndef Getbplist
#define Getbplist

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "cJSON.h"

#include "utils/core/network/Basic.h"
#include "utils/core/op/Generic.h"

void get_bplist(int uid,uint8_t mode_id,int offset,int limit,const char* token);
int* getsids(void);

#endif /* Getbplist_h */

