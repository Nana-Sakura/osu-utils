#ifndef Query_hh
#define Query_hh

#include <string>

#include "utils/core/network/Requests.hh"
#include "utils/util/Commons.hh"

namespace Utils
{
    namespace Op
    {

        std::string get_score_list(struct Utils::Commons::personal_info info, struct Utils::Commons::BeatmapSet_Range range, int check_target, int include_fails, const std::string& cc_token);

        std::string get_beatmap_score(struct Utils::Commons::personal_info info, int beatmap_id, const std::string& cc_token);

        std::string get_beatmap_info(int beatmap_id, const std::string& cc_token);

        std::string get_own_personal_info(const std::string& acg_token);

        std::string get_personal_info(const std::string& username, const std::string& cc_token);

    }// namespace Op
}// namespace Utils

#endif /* Query_hh */