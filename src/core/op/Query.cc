#include "utils/core/op/Query.hh"
#include "utils/util/Commons.hh"
#include <sstream>

namespace Utils
{
    namespace Op
    {

        std::string get_score_list(struct Utils::Commons::personal_info info, struct Utils::Commons::BeatmapSet_Range range, int check_target, int include_fails, const std::string& cc_token)
        {
            std::stringstream url;
            url << "https://osu.ppy.sh/api/v2/users/" << info.uid << "/scores/" << check_target_Strings[check_target] << "?include_fails=" << include_fails << "&mode=" << osu_mode_Strings[info.mode] << "&limit=" << range.limit << "&offset=" << range.offset;
            Utils::Network::Requests query(url.str(), "", cc_token);
            return query.curl_get_request();
        }

        std::string get_beatmap_score(struct Utils::Commons::personal_info info, int beatmap_id, const std::string& cc_token)
        {
            std::stringstream url;
            url << "https://osu.ppy.sh/api/v2/beatmaps/" << beatmap_id << "/scores/users/" << info.uid << "?mode=" << osu_mode_Strings[info.mode] << "&mods=minus";
            Utils::Network::Requests query(url.str(), "", cc_token);
            return query.curl_get_request();
        }

        std::string get_beatmap_info(int beatmap_id, const std::string& cc_token)
        {
            std::stringstream url;
            url << "https://osu.ppy.sh/api/v2/beatmaps/lookup?id=" << beatmap_id;
            Utils::Network::Requests query(url.str(), "", cc_token);
            return query.curl_get_request();
        }

        std::string get_own_personal_info(const std::string& acg_token)
        {
            Utils::Network::Requests query("https://osu.ppy.sh/api/v2/me", "", acg_token);
            return query.curl_get_request();
        }

        std::string get_personal_info(const std::string& username, const std::string& cc_token)
        {
            std::stringstream url;
            url << "https://osu.ppy.sh/api/v2/users/" << username;
            Utils::Network::Requests query(url.str(), "", cc_token);
            return query.curl_get_request();
        }

    }// namespace Op
}// namespace Utils