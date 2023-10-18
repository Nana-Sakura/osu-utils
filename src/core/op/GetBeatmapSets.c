#include "utils/core/op/GetBeatmapSets.h"

void get_beatmapsets(const char* cc_token){

    int offset,limit,r;

    struct personal_info info=manual_get_info();

    printf("Type in if you want to download all of the beatmaps on the list(0 for Yes, 1 for No): ");
    while((scanf("%d",&r)<1)||(r<0)||(r>1)){
        LOG("Option format error, please type in again.");
        fflush(stdin);
    }

    if(r){
        printf("Type in the start position of the bplist you want to get(0 for default): ");
        while((scanf("%d",&offset)<1)||(offset>100)){
            LOG("Offset format error, please type in again.");
            fflush(stdin);
        }

        printf("Type in the end position of the bplist you want to get(100 for default): ");
        while((scanf("%d",&limit)<1)||(limit>100)){
            LOG("Limit format error, please type in again.");
            fflush(stdin);
        }
    }
    else{
        offset=0;
        limit=100;
    }

    // Then get bplist.

    char* score_list=get_score_list(info,offset,limit,best,0,cc_token);

    // Simply download.

    map_downloader(score_list,offset,limit);

    free(score_list);
}
