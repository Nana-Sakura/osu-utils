#ifndef Calc_h
#define Calc_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "cJSON.h"

#include "utils/extra/calc/Calc.h"

#define perfect_value ((const int[]){300,305,315,320})

struct statistics_mania{
    uint32_t perfect;
    uint32_t great;
    uint32_t good;
    uint32_t ok;
    uint32_t meh;
    uint32_t miss;
    float sr;
};

enum perfect{
    Score_V1=0,
    Score_V2=1,
    Score_Lazer=2,
    Score_PP=3
};

float difficulty(float accpp);
float acc_calc(int pft,struct statistics_mania i);
float multiplier(cJSON* mods);
float maximumpp(struct statistics_mania i,float multiplier);
void mania_pp(struct statistics_mania i,cJSON* mods);

#endif /* Calcpp_h */