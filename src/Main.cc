#include <curl/curl.h>
#include <log.hh>
#include "utils/core/op/Token.hh"
#include "utils/core/op/GetBPA.hh"
#include "utils/core/op/CheckScore.hh"
#include "utils/core/op/GetBeatmapSets.hh"
#include "utils/core/profile/AccountProfile.hh"
#include "utils/uic/CommandLine.hh"
#include "utils/util/Commons.hh"
#include "utils/extra/calc/CalcManiaPP.hh"

int main(void){
    if(Utils::Commons::get_file_size("Cache")==-1){
        std::filesystem::create_directory("Cache",".");
    }
    curl_global_init(CURL_GLOBAL_ALL);
    std::string cc_token=Utils::Op::get_token(Utils::Commons::CC);
    while(1){
        if(Utils::Commons::check_expire(file_target_Strings[Utils::Commons::CC])){
            cc_token=Utils::Op::get_token(Utils::Commons::CC);
        }
        switch(Utils::UIC::menu_select()){
        case 0:
            LOG("Exiting...");
//            curl_global_cleanup();
            exit(0);
            break;
        case 1:
            Utils::Op::get_beatmapsets(cc_token);
            break;
        case 2:
            Utils::Op::get_bp_analyze(Utils::Commons::SELF,cc_token);
            break;
        case 3:
            Utils::Op::check_specified_score(Utils::Commons::SELF,cc_token);
            break;
        case 4:
            Utils::Op::check_recent_score(Utils::Commons::SELF,Utils::Commons::RECENT,Utils::Commons::EXCLUDES,cc_token);
            break;
        case 5:
            Utils::Op::check_recent_score(Utils::Commons::SELF,Utils::Commons::RECENT,Utils::Commons::INCLUDES,cc_token);
            break;
        case 6:
            Utils::Op::get_bp_analyze(Utils::Commons::OTHERS,cc_token);
            break;
        case 7:
            Utils::Op::check_specified_score(Utils::Commons::OTHERS,cc_token);
            break;
        case 8:
            Utils::Op::check_recent_score(Utils::Commons::OTHERS,Utils::Commons::RECENT,Utils::Commons::EXCLUDES,cc_token);
            break;
        case 9:
            Utils::Op::check_recent_score(Utils::Commons::OTHERS,Utils::Commons::RECENT,Utils::Commons::INCLUDES,cc_token);
            break;
        case 10:
            Utils::Extra::Calc::calc_mania_pp();
            break;
        case 99:
            Utils::Profile::write_user_info(Utils::Profile::query_self_info());
            break;
        default:
            LOG("Invaild input.");
            break;
        }
    }
    
}
