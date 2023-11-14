#ifndef OAuth_h
#define OAuth_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <cJSON.h>
#include <log.h>

#include "utils/core/network/Requests.h"
#include "utils/core/network/Socket.h"
#include "utils/util/Generic.h"

char* get_client_credential_token(void);
char* get_authorization_code_grant_token(void);
char* read_token(int token_type);
int write_token(int token_type,const char* token_json);
void get_code_request(void);
void get_token(int token_type);

#endif /* OAuth_h */
