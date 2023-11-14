#ifndef Downloader_h
#define Downloader_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <cJSON.h>
#include <log.h>

#include "utils/core/network/Requests.h"
#include "utils/util/Generic.h"

int compare(const void* p1,const void* p2);
void map_downloader(char* score_list,int offset,int limit);

#endif /* Downloader_h */
