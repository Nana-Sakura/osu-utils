#ifndef Score_h
#define Score_h

#include <stdio.h>
#include <time.h>
#include <cJSON.h>
#include <log.h>

#include "utils/core/network/Requests.h"
#include "utils/core/op/Query.h"
#include "utils/util/Generic.h"

void get_score(char* beatmap_score,char* beatmap_info);
void get_recent(char* rct,const char* token);

#endif /* Score_h */