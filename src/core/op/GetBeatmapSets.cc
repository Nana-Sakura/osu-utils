#include "utils/core/network/Download.hh"
#include "utils/core/op/GetBeatmapSets.hh"
#include "utils/core/op/Query.hh"
#include "utils/core/profile/AccountProfile.hh"
#include "utils/uic/CommandLine.hh"

namespace Utils{
    namespace Op{

        void get_beatmapsets(const std::string& cc_token){
            struct Utils::Commons::personal_info info=Utils::Profile::get_info(Utils::Commons::OTHERS,cc_token);
            struct Utils::Commons::BeatmapSet_Range range=Utils::UIC::get_beatmapset_range();
            std::string score_list=Utils::Op::get_score_list(info,range,Utils::Commons::BEST,Utils::Commons::EXCLUDES,cc_token);
            Utils::Network::map_downloader(score_list,range);
        }
        
    }
}