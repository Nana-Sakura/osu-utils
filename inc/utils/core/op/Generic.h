//
//  Generic.h
//  osu-utils
//
//  Created by Merry on 2023/9/20.
//

#ifndef Generic_h
#define Generic_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "cJSON.h"

#include "log.h"
#include "utils/core/network/Downloader.h"
#include "utils/core/network/Getbplist.h"
#include "utils/core/op/Bpanalyze.h"

char* select_mode(int mode_id);
bool test_file_existence(char* path);
char* read_file(const char* path);
int menu_select(void);
void Getbeatmapsets(const char* token);
void Bpa(const char* token);
void Bpame(const char* token);
void Setid(void);

#endif /* Generic_h */
