#ifndef Analyze_h
#define Analyze_h

#include <stdio.h>
#include <string.h>
#include <cJSON.h>

#include "utils/util/Generic.h"

struct ranking_analyze{
    int s;
    int sh;
    int x;
    int xh;
    int fc;
    float avgpp;
    float ppmax;
    float ppmin;
};

void score_analyze(struct personal_info info,char* score_list);

#endif /* Analyze_h */