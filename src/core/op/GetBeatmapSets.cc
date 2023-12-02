#include "utils/core/op/GetBeatmapSets.hh"
#include "utils/core/network/Download.hh"
#include "utils/core/op/Query.hh"
#include "utils/core/profile/AccountProfile.hh"
#include "utils/uic/CommandLine.hh"
#include <log.hh>

namespace Utils
{
    namespace Op
    {

        void get_beatmapsets(const std::string& cc_token)
        {

            struct Utils::Commons::personal_info info = Utils::Profile::get_info(Utils::Commons::OTHERS, cc_token);
            if(info.uid == 0)
            {
                LOG("This user does not exist or facing network error.");
                return;
            }

            struct Utils::Commons::BeatmapSet_Range range = Utils::UIC::get_beatmapset_range();

            std::string score_list = Utils::Op::get_score_list(info, range, Utils::Commons::BEST, Utils::Commons::EXCLUDES, cc_token);
            if(!score_list.compare(""))
            {
                LOG("Unable to get score list of the user, please check your network status.");
                return;
            }
            if(!score_list.compare("[]"))
            {
                LOG("This user is confirmed that has not played yet.");
                return;
            }

            int if_video = Utils::UIC::request_video_confirm();

            Utils::Network::map_downloader(score_list, range, if_video);
        }
    }// namespace Op
}// namespace Utils
