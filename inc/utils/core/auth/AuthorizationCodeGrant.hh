#ifndef AuthorizationCodeGrant_hh
#define AuthorizationCodeGrant_hh

#include "utils/core/network/Requests.hh"
#include "utils/uic/CommandLine.hh"

namespace Utils{
    namespace OAuth{

        std::string get_authorization_code_grant_token(void);
        
    }
}

#endif /* AuthorizationCodeGrant_hh */