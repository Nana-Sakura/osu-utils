#include <log.hh>
#include <sstream>

#include "utils/core/network/Requests.hh"

namespace Utils
{
    namespace OAuth
    {

        std::string get_client_credential_token(void)
        {
            std::stringstream s;
            s << "client_id=" << clientid << "&client_secret=" << clientsec << "&grant_type=client_credentials&scope=public";
            Utils::Network::Requests req("https://osu.ppy.sh/oauth/token", s.str(), " ");
            return req.curl_post_request();
        }

    }// namespace OAuth
}// namespace Utils
