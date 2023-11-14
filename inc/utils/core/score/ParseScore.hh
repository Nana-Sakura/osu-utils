#ifndef ParseScore_hh
#define ParseScore_hh

#include <string>

namespace Utils{
    namespace Score{

        void parse_specified_score(const std::string& beatmap_score,const std::string& beatmap_info);
        void parse_recent_score(const std::string& recent_score,const std::string& cc_token);

    }
}

#endif /* ParseScore_hh */
