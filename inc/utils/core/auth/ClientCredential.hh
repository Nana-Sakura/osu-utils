#ifndef ClientCredential_hh
#define ClientCredential_hh

#include <string>

#define clientid 24548
#define clientsec "8ZNaZq1uUo3FF3IHTOQMMXBPicf1Hcj2I1RmdBhY"

namespace Utils{
    namespace OAuth{

        std::string get_client_credential_token(void);
        
    }
}

#endif /* ClientCredential_hh */