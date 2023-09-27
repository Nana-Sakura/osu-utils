//
//  Getbplist.h
//  osu-utils
//
//  Created by Merry on 2023/9/20.
//

#ifndef Getbplist_h
#define Getbplist_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#include "utils/core/network/Basic.h"
#include "utils/core/op/Generic.h"

char* get_bplist(int uid,int mode_id,int offset,int limit,const char* token);

#endif /* Getbplist_h */

