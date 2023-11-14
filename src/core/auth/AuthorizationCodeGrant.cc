#include <sstream>
#include <log.hh>

#include "utils/core/auth/AuthorizationCodeGrant.hh"
#include "utils/util/Commons.hh"

namespace Utils{
    namespace OAuth{

        std::string get_authorization_code_grant_token(void){
            while(Utils::Commons::get_file_size("Cache/code")==-1){
                LOG("Please authorize before using this function.");
                Utils::UIC::get_code_request();
            }
            std::string code=Utils::Commons::read_file("Cache/code");
            std::stringstream s;
            s<<"client_id="<<clientid<<"&client_secret="<<clientsec<<"&code="<<code<<"&grant_type=authorization_code&redirect_uri=http://localhost:4000";
            Utils::Network::Requests req("https://osu.ppy.sh/oauth/token",s.str()," ");
            return req.curl_post_request();
        }

    }
}
