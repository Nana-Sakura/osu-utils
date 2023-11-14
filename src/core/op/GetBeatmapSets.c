#include "utils/core/op/GetBeatmapSets.h"

void get_beatmapsets(const char* cc_token){

    struct personal_info info=manual_get_info();

    struct BeatmapSet_Range range=get_beatmapset_range();

    // Then get bplist.

    char* score_list=get_score_list(info,range.offset,range.limit,best,0,cc_token);

    // Simply download.

    map_downloader(score_list,range.offset,range.limit);

    free(score_list);
}
