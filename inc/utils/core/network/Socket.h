//
//  Socket.h
//  osu-utils
//
//  Created by Merry on 2023/9/24.
//

#ifndef Socket_h
#define Socket_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/uio.h>
#include "log.h"

// Not going to use Socket currently.

char* receive_code(void);

#endif /* Socket_h */