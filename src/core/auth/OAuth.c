#include "utils/core/auth/OAuth.h"

const int clientid=24548;
const char* clientsec="8ZNaZq1uUo3FF3IHTOQMMXBPicf1Hcj2I1RmdBhY";

char* get_client_credential_token(void){

    char data[150];
    sprintf(data,"client_id=%d&client_secret=%s&grant_type=client_credentials&scope=public",clientid,clientsec);
    
    return curl_post_request(data);
}

char* get_authorization_code_grant_token(void){

    char data[1200]={'\0'};

    int fails=0;
    while(get_file_size("Cache/code")==-1){
        LOG("Please authorize before using this function.");
        get_code_request();
        fails++;
        if(fails>3){
            LOG("Failed to get code, may be Network Error?");
            exit(16);
        }
    }
    char* code=read_file("Cache/code");
    sprintf(data,"client_id=%d&client_secret=%s&code=%s&grant_type=authorization_code&redirect_uri=http://localhost:4000",clientid,clientsec,code);
    char* token_json=curl_post_request(data);
    
    // Cleanup.

    free(code);
    
    return token_json;
}

char* read_token(int token_type){

    const char* path=(token_type)?"Cache/cc_token":"Cache/acg_token";

    // Prepare requsitions.

    int fails=0;

    while(get_file_size(path)==-1){
        LOG("Token not exist, will get one.");
        get_token(token_type);
        fails++;
        if(fails>3){
            LOG("Failed to get token, may be Network Error?");
            exit(16);
        }
    }

    while(check_expire(path)){
        LOG("Token expired, will get another one.");
        get_token(token_type);
        fails++;
        if(fails>3){
            LOG("Failed to get token, may be Network Error?");
            exit(16);
        }
    }

    // Directly read.

    LOG("Reading token...");

    return read_file(path);
}

int write_token(int token_type,const char* token_json){

    // Parse json response to extract token.

    cJSON* root=cJSON_Parse(token_json);
    cJSON* item=cJSON_GetObjectItem(root,"access_token");

    // Exception Process.

    if(item==NULL){
        cJSON_Delete(root);
        return -1;
    }

    char* token=item->valuestring;

    // Simply write.

    const char* path=(token_type)?"Cache/cc_token":"Cache/acg_token";

    write_file(path,token,"w+");

    // Cleanup.

    cJSON_Delete(root);

    return 0;
}

void get_code_request(void){
    
    printf("%s","https://osu.ppy.sh/oauth/authorize?client_id=24548&redirect_uri=http://localhost:4000&response_type=code&scope=public+identify\n");
    printf("%s","Please copy the link above to your browser and then click on \"Authorize\" button.\n");
    
    char* code=receive_code();
    write_file("Cache/code",code,"w+");

    // Cleanup.

    free(code);
}

void get_token(int token_type){

    char* token_json=(token_type)?get_client_credential_token():get_authorization_code_grant_token();

    write_token(token_type,token_json);

    // Cleanup.

    free(token_json);
}
