#ifndef Request_hh
#define Request_hh

#include <string>

#include "utils/core/auth/ClientCredential.hh"
#include "utils/core/network/Requests.hh"

namespace Utils
{
    namespace Network
    {

        struct memory {
            char* response;
            size_t size;
        };

        class Requests {

        private:
            std::string url;
            std::string data;
            std::string token;
            struct memory chunk;

        public:
            Requests(const std::string& u, const std::string& d, const std::string& cc_token);
            std::string curl_get_request();
            std::string curl_post_request();
            std::string curl_get_object_request();

            ~Requests();
        };

        ssize_t cb(char* buffer, size_t size, size_t nitems, void* userdata);

    }// namespace Network
}// namespace Utils

#endif /* Request_hh */
