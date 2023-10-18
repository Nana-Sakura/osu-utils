#include "utils/core/op/GetBPA.h"

void get_bp_analyze(int target,const char* cc_token){
    struct personal_info info=(target)?read_info():semi_auto_get_info(cc_token);
    
    char* score_list=get_score_list(info,0,100,best,excludes,cc_token);
    
    score_analyze(info,score_list);

    free(score_list);
}
