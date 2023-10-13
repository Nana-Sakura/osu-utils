//
//  Getscore.h
//  osu-utils
//
//  Created by Merry on 2023/9/28.
//

#ifndef Getscore_h
#define Getscore_h

#include <stdio.h>
#include <curl/curl.h>
#include <time.h>
#include "cJSON.h"

#include "log.h"
#include "utils/core/network/Basic.h"
#include "utils/core/op/Generic.h"

char* get_score_list(int uid,int mode_id,int offset,int limit,int check_mode_id,int include_fails,const char* token);
char* get_beatmap_score(int uid,int mode_id,int beatmap_id,const char* token);
char* get_beatmap_info(int beatmap_id,const char* token);
void get_score(char* beatmapscore,char* beatmapinfo);
void get_recent(char* rct,const char* token);

#endif /* Getscore_h */
