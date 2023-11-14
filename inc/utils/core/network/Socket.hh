#ifndef Socket_hh
#define Socket_hh

#include <string>
#if defined(_WIN32)||defined(__WIN32__)||defined(__MINGW32__)
#include <winsock.h>
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

namespace Utils{
    namespace Network{
        #if defined (_WIN32)||defined(__WIN32__)||defined(__MINGW32__)
        int inet_aton(const char *cp, struct in_addr *addr);
        #endif
        std::string receive_code(void);
        
    }
}

#endif /* Socket_hh */
