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
#include "utils/core/op/Bpanalyze.h"
#include "utils/core/op/Score.h"
#include "utils/core/op/Calcpp.h"

struct personal_info{
    int uid;
    int mode;
};

struct statistics_osu{
    uint32_t great;
    uint32_t ok;
    uint32_t meh;
    uint32_t miss;
    uint32_t combo;
};

struct beatmap{
    uint32_t max_combo;
    uint32_t circles;
    uint32_t sliders;
    uint32_t spinners;
    
};

char* select_mode(int mode_id);
char* select_check_mode(int check_mode_id);
bool test_file_existence(char* path);
char* read_file(const char* path);
int menu_select(void);
void get_beatmapsets(const char* token);
void Bpa(int check_mode,const char* token);
void Setid(void);
char* mod_intro(cJSON* mods);
void score(int info_get_mode,const char* token);
void recent(int score_request_mode,int info_get_mode,int include_fails,const char* token);
struct personal_info get_info(int check_mode);
char* strfsec(int length);
void calc_mania_pp(void);

#endif /* Generic_h */
