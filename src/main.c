#include <stdio.h>
#include <curl/curl.h>

#include "utils/core/auth/OAuth.h"
#include "utils/core/op/CalcManiaPP.h"
#include "utils/core/op/CheckScore.h"
#include "utils/core/op/GetBeatmapSets.h"
#include "utils/core/op/GetBPA.h"
#include "utils/core/util/Generic.h"
#include "utils/core/uic/CommandLine.h"

int main(void){
    if(get_file_size("Cache")==-1){
        mkdir("Cache",0755);
    }
    curl_global_init(CURL_GLOBAL_ALL);
    char* cc_token=read_token(1);
    while(1){
        switch(menu_select()){
        case 0:
            LOG("Exiting...");
//            curl_global_cleanup();
            exit(0);
            break;
        case 1:
            get_beatmapsets(cc_token);
            break;
        case 2:
            get_bp_analyze(self,cc_token);
            break;
        case 3:
            score(self,cc_token);
            break;
        case 4:
            recent_score(self,recent,excludes,cc_token);
            break;
        case 5:
            recent_score(self,recent,includes,cc_token);
            break;
        case 6:
            get_bp_analyze(others,cc_token);
            break;
        case 7:
            score(others,cc_token);
            break;
        case 8:
            recent_score(others,recent,excludes,cc_token);
            break;
        case 9:
            recent_score(others,recent,includes,cc_token);
            break;
        case 10:
            calc_mania_pp();
            break;
        case 99:
            auto_set_id();
            break;
        default:
            LOG("Invaild input.");
            break;
        }
    }
}