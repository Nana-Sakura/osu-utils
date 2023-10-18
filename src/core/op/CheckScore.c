#include "utils/core/op/CheckScore.h"

void score(int target,const char* cc_token){
    
    int beatmap_id;

    printf("Type in beatmap id: ");
    while(scanf("%d",&beatmap_id)<1){
        LOG("beatmap id format error, please type in again.");
        fflush(stdin);
    }

    struct personal_info info=(target)?read_info():semi_auto_get_info(cc_token);
    
    char* beatmap_score=get_beatmap_score(info,beatmap_id,cc_token);
    char* beatmap_info=get_beatmap_info(beatmap_id,cc_token);

    get_score(beatmap_score,beatmap_info);

    free(beatmap_info);
    free(beatmap_score);
}

void recent_score(int target,int check_target,int include_fails,const char* cc_token){
    
    struct personal_info info=(target)?read_info():semi_auto_get_info(cc_token);
    
    char* score_list=get_score_list(info,0,1,check_target,include_fails,cc_token);
    
    get_recent(score_list,cc_token);
    
    free(score_list);
}
