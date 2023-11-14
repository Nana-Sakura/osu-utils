#include <sstream>
#include <log.hh>

#include "utils/core/network/Socket.hh"

namespace Utils{
    namespace Network{

        #if defined (_WIN32)||defined(__WIN32__)||defined(__MINGW32__)
        int inet_aton(const char *cp, struct in_addr *addr){
            addr->s_addr=inet_addr(cp);
            return (addr->s_addr == INADDR_NONE)?0:1;
        }
        #endif

        std::string receive_code(void){
            char readbuf[4096]={'\0'};
            std::stringstream code;

            int s_fd=socket(AF_INET,SOCK_STREAM,0);
            struct sockaddr_in server_addr;
            server_addr.sin_family=AF_INET;
            server_addr.sin_port=htons(4000);
            inet_aton("127.0.0.1",&server_addr.sin_addr);
            bind(s_fd,(struct sockaddr*)&server_addr,sizeof(struct sockaddr_in));
            listen(s_fd,10);
            
            int c_fd=accept(s_fd,NULL,NULL);
            recv(c_fd,readbuf,sizeof(readbuf),0);
            LOG("Read success.");
            printf("%s",readbuf);
            for(int i=11;readbuf[i]!=' ';i++){
                code<<readbuf[i];
            }
            
            return code.str();
        }

    }
}
