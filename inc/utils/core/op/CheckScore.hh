#ifndef CheckScore_hh
#define CheckScore_hh

#include <string>

namespace Utils
{
    namespace Op
    {

        void check_specified_score(int target_entity, const std::string& cc_token);

        void check_recent_score(int target_entity, int check_target, int include_fails, const std::string& cc_token);

    }// namespace Op
}// namespace Utils

#endif /* CheckScore_hh */