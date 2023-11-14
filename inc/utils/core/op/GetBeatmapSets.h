#ifndef GetBeatmapSets_h
#define GetBeatmapSets_h

#include <stdio.h>
#include <log.h>

#include "utils/core/op/Query.h"
#include "utils/core/network/Downloader.h"
#include "utils/core/profile/AccountProfile.h"
#include "utils/uic/CommandLine.h"

struct BeatmapSet_Range{
    int offset;
    int limit;
};

void get_beatmapsets(const char* token);

#endif /* GetBeatmapSets_h */
