//
//  OAuth.h
//  osu-utils
//
//  Created by Merry on 2023/9/20.
//

#ifndef OAuth_h
#define OAuth_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <curl/curl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "cJSON.h"
#include "log.h"
#include "utils/core/network/Basic.h"
#include "utils/core/op/Generic.h"

void read_token(char* tokenstring,int fails);
char* read_code(void);
void get_token(void);
void get_client_credential_token(int clientid,const char* clientsec);
void get_authorization_code_grant_token(int clientid,const char* clientsec,const char* code);
void write_token(char* buffer);
void get_code_request(void);

#endif /* OAuth_h */
