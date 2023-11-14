#ifndef CommandLine_h
#define CommandLine_h

#include <stdio.h>
#include <log.h>

#include "utils/core/op/GetBeatmapSets.h"
#include "utils/util/Generic.h"
#include "utils/extra/calc/Calc.h"

int menu_select(void);
struct statistics_mania get_result_info(void);
cJSON* get_essential_mods(void);
struct personal_info manual_get_info(void);
int get_beatmap_id(void);
struct BeatmapSet_Range get_beatmapset_range(void);

#endif /* CommandLine_h */
