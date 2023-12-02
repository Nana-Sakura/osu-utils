#include "utils/core/op/CheckScore.hh"
#include "utils/core/op/Query.hh"
#include "utils/core/profile/AccountProfile.hh"
#include "utils/core/score/ParseScore.hh"
#include "utils/uic/CommandLine.hh"
#include "utils/util/Commons.hh"
#include <log.hh>

namespace Utils
{
    namespace Op
    {

        void check_specified_score(int target_entity, const std::string& cc_token)
        {

            struct Utils::Commons::personal_info info = Utils::Profile::get_info(target_entity, cc_token);
            if(info.uid == 0)
            {
                LOG("Unable to get info of the user, please check your input or network status.");
                return;
            }

            int beatmap_id = Utils::UIC::get_beatmap_id();
            std::string beatmap_score = get_beatmap_score(info, beatmap_id, cc_token);
            if(!beatmap_score.compare(""))
            {
                LOG("Unable to get score on this beatmap, please check your network status.");
                return;
            }
            if(!beatmap_score.compare("{\"error\":null}"))
            {
                LOG("The user is confirmed that have not played on this map yet.");
                return;
            }

            // Nothing will stop the Checking Progress Now.

            std::string beatmap_info = get_beatmap_info(beatmap_id, cc_token);
            if(!beatmap_info.compare(""))
            {
                LOG("Unable to get info of this beatmap, please check your network status.");
                return;
            }

            Utils::Score::parse_specified_score(beatmap_score, beatmap_info);
        }

        void check_recent_score(int target_entity, int check_target, int include_fails, const std::string& cc_token)
        {
            struct Utils::Commons::BeatmapSet_Range range = {0};
            range.offset = 0;
            range.limit = 1;

            struct Utils::Commons::personal_info info = Utils::Profile::get_info(target_entity, cc_token);
            if(info.uid == 0)
            {
                LOG("Unable to get info of the user, please check your input or network status.");
                return;
            }

            std::string score_list = get_score_list(info, range, check_target, include_fails, cc_token);
            if(!score_list.compare(""))
            {
                LOG("Unable to get score list, please check your network status.");
                return;
            }

            Utils::Score::parse_recent_score(score_list, cc_token);
        }
    }// namespace Op
}// namespace Utils
