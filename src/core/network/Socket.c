#include "utils/core/network/Socket.h"

char* receive_code(void){
    int s_fd;
    char readbuf[4096]={'\0'};
    char* code=malloc(1024*sizeof(char));

    // Monitor localhost:4000.

    s_fd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in s_addr;
    s_addr.sin_family=AF_INET;
    s_addr.sin_port=htons(4000);
    inet_aton("127.0.0.1",&s_addr.sin_addr);
    bind(s_fd,(struct sockaddr*)&s_addr,sizeof(struct sockaddr_in));
    listen(s_fd,10);
    
    // Just read GET method parameters.

    int c_fd=accept(s_fd,NULL,NULL);
    read(c_fd,readbuf,sizeof(readbuf));
    LOG("Read success.");
    write(c_fd,"Successfully get access.",strlen("Successfully get access."));

    // Regex is totally not needed.

    int j=0;
    for(int i=11;readbuf[i]!=' ';i++){
        code[j++]=readbuf[i];
    }

    return code;
}
