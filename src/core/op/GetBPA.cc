#include <log.hh>
#include "utils/core/op/GetBPA.hh"
#include "utils/core/op/Query.hh"
#include "utils/core/profile/AccountProfile.hh"
#include "utils/core/score/Analyze.hh"
#include "utils/util/Commons.hh"

namespace Utils{
    namespace Op{

        void get_bp_analyze(int target,const std::string& cc_token){
            struct Utils::Commons::BeatmapSet_Range range={0};
            range.offset=0;
            range.limit=100;
            struct Utils::Commons::personal_info info=Utils::Profile::get_info(target,cc_token);
            
            if(info.uid==0){
                LOG("This user does not exist or facing network error.");
                return;
            }
            
            std::string score_list=Utils::Op::get_score_list(info,range,Utils::Commons::BEST,Utils::Commons::EXCLUDES,cc_token);
            Utils::Score::score_analyze(info,score_list);
        }

    }
}
