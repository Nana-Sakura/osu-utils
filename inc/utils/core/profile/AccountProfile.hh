#ifndef AccountProfile_hh
#define AccountProfile_hh

#include "utils/util/Commons.hh"

namespace Utils{
    namespace Profile{

        struct Utils::Commons::personal_info query_info(const std::string& cc_token);
        
        struct Utils::Commons::personal_info query_self_info(void);
        
        struct Utils::Commons::personal_info parse_info(const std::string& info_json);

        struct Utils::Commons::personal_info read_info(void);

        void write_user_info(struct Utils::Commons::personal_info info);

        struct Utils::Commons::personal_info get_info(int info_type,const std::string& cc_token);
        
    }
}


#endif /* AccountProfile_hh */