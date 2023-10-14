//
//  Downloader.h
//  osu-utils
//
//  Created by Merry on 2023/9/20.
//

#ifndef Downloader_h
#define Downloader_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <curl/curl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "cJSON.h"

#include "log.h"
#include "utils/core/network/Basic.h"
#include "utils/core/op/Generic.h"

int compare(const void* p1,const void* p2);
void mapdownloader(char* bplist,int offset,int limit);

#endif /* Downloader_h */
