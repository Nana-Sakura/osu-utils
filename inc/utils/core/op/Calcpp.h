//
//  Calcpp.h
//  osu-utils
//
//  Created by Merry on 2023/10/4.
//

#ifndef Calcpp_h
#define Calcpp_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "cJSON.h"

#include "utils/core/op/Calcpp.h"
#include "utils/core/op/Generic.h"

struct statistics_mania{
    uint32_t perfect;
    uint32_t great;
    uint32_t good;
    uint32_t ok;
    uint32_t meh;
    uint32_t miss;
    float sr;
};

float difficulty(float accpp);
int perfect_value(int score_mode);
float acc_calc(int score_mode,struct statistics_mania i);
float multiplier(cJSON* mods);
float maximumpp(struct statistics_mania i,float multiplier);
void mania_pp(struct statistics_mania i,cJSON* mods);

#endif /* Calcpp_h */