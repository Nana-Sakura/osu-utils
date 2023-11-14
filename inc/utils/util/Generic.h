#ifndef Generic_h
#define Generic_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <cJSON.h>
#include <log.h>

#if defined (_WIN32)||defined(__WIN32__)||defined(__MINGW32__)||(defined(__linux__)&&!defined(__ANDROID__))
#define st_mtimespec st_mtim
#endif

#define osu_mode_Strings ((const char*[]){"osu","taiko","fruits","mania"})

#define check_target_Strings ((const char*[]){"best","recent","firsts"})

struct personal_info{
    uint32_t uid;
    uint32_t mode;
};

enum osu_mode{
    osu=0,
    taiko=1,
    fruits=2,
    mania=3
};

enum check_target{
    best=0,
    recent=1,
    firsts=2
};

enum target{
    others=0,
    self=1
};

enum include_fails{
    excludes=0,
    includes=1
};

void write_file(const char* path_to_file,const char* file_content,const char* write_mode);
char* read_file(const char* path);
size_t get_file_size(const char* path);
time_t get_last_modified_time(const char* path);
int check_expire(const char* path);

char* strfsec(int length);
char* strf_mod_intro(cJSON* mods);
void show_progress(int task_now,int task_sum,int width);

int search_array(const char** array,int len,const char* val);

#endif /* Generic_h */
