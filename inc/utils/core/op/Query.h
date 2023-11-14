#ifndef Query_h
#define Query_h

#include <stdio.h>
#include <curl/curl.h>
#include <cJSON.h>
#include <log.h>

#include "utils/core/network/Requests.h"
#include "utils/util/Generic.h"

char* get_score_list(struct personal_info info,int offset,int limit,int check_target,int include_fails,const char* token);
char* get_beatmap_score(struct personal_info info,int beatmap_id,const char* token);
char* get_beatmap_info(int beatmap_id,const char* token);
char* get_own_personal_info(const char* acg_token);
char* get_personal_info(const char* username,const char* cc_token);

#endif /* Query_h */
