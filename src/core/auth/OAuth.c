//
//  OAuth.c
//  osu-utils
//
//  Created by Merry on 2023/9/20.
//

#include "utils/core/auth/OAuth.h"

void read_token(char* tokenstring,int fails){

    // Avoid endless self-call.

    if(fails>1){
        LOG("Failed to read and get token.\n");
        exit(64);
    }
    
    // Simply read the file, regardless of anything.

    char* buffer;
    buffer=read_file("Cache/token.json");

    if(buffer){
        cJSON* root=cJSON_Parse(buffer);

        // Must free buffer or memory will leak.

        free(buffer);
        
        // Check if token expired.
        
        cJSON* timethen=cJSON_GetObjectItem(root,"time");
        time_t previous_time=timethen->valueint;
        time_t current_time=time(NULL);
        if(current_time-previous_time>=86400){
            fails++;
            LOG("Token expired, will get another.\n");
            get_token();
            read_token(tokenstring,fails);
        }
        
        // Take token out of file.

        cJSON* token=cJSON_GetObjectItem(root,"token");
        sprintf(tokenstring,"%s",token->valuestring);
        cJSON_Delete(root);
    }
    else{

        // It's impossible, isn't it.

        fails++;
        LOG("File is empty, maybe network error, will get another token.\n");
        read_token(tokenstring,fails);
    }
}

char* read_code(void){

    // Simply read the file, regardless of anything.
    
    char* string=read_file("Cache/code");
    if(!string){
        LOG("Code file exists but it is empty, you have to get another one.");
        exit(64);
    }
    return string;
}

void get_client_credential_token(int clientid,const char* clientsec){
    CURL* eh=curl_easy_init();
    if(eh){
        struct memory chunk={0};
        struct curl_slist* list;
        char data[150]={'\0'};
        sprintf(data,"client_id=%d&client_secret=%s&grant_type=client_credentials&scope=public",clientid,clientsec);
        list=curl_slist_append(NULL,"Accept: application/json");
        list=curl_slist_append(list,"Content-Type: application/x-www-form-urlencoded");
        curl_easy_setopt(eh,CURLOPT_URL,"https://osu.ppy.sh/oauth/token");
        curl_easy_setopt(eh,CURLOPT_HTTPHEADER,list);
        curl_easy_setopt(eh,CURLOPT_POSTFIELDSIZE,(long)strlen(data));
        curl_easy_setopt(eh,CURLOPT_POSTFIELDS,data);
        curl_easy_setopt(eh,CURLOPT_WRITEFUNCTION,cb);
        curl_easy_setopt(eh,CURLOPT_WRITEDATA,(void*) &chunk);
        curl_easy_setopt(eh,CURLOPT_TIMEOUT,30);
        curl_easy_perform(eh);

        // Token has to be written to file.
        
        write_token(chunk.response);

        // Cleanup.

        free(chunk.response);
        curl_easy_cleanup(eh);
    }
    else{

        // It's totally impossible, isn't it.

        LOG("Failed to make a curl handle.\n");
        exit(1);
    }
}

void get_authorization_code_grant_token(int clientid,const char* clientsec,const char* code){
    CURL* eh=curl_easy_init();
    if(eh){
        struct memory chunk={0};
        struct curl_slist* list;
        char data[1200]={'\0'};
        sprintf(data,"client_id=%d&client_secret=%s&code=%s&grant_type=authorization_code&redirect_uri=http://localhost:4000",clientid,clientsec,code);
        list=curl_slist_append(NULL,"Accept: application/json");
        list=curl_slist_append(list,"Content-Type: application/x-www-form-urlencoded");
        curl_easy_setopt(eh,CURLOPT_URL,"https://osu.ppy.sh/oauth/token");
        curl_easy_setopt(eh,CURLOPT_HTTPHEADER,list);
        curl_easy_setopt(eh,CURLOPT_POSTFIELDSIZE,(long)strlen(data));
        curl_easy_setopt(eh,CURLOPT_POSTFIELDS,data);
        curl_easy_setopt(eh,CURLOPT_WRITEFUNCTION,cb);
        curl_easy_setopt(eh,CURLOPT_WRITEDATA,(void*) &chunk);
        curl_easy_setopt(eh,CURLOPT_TIMEOUT,30);
        curl_easy_perform(eh);

        // Token has to be written to file.
        
        write_token(chunk.response);

        // Cleanup.

        free(chunk.response);
        curl_easy_cleanup(eh);
    }
    else{

        // It's totally impossible, isn't it.

        LOG("Failed to make a curl handle.\n");
        exit(1);
    }
}

void get_token(void){

    // osu-util application client imformation

    int clientid=24548;
    const char* clientsec="8ZNaZq1uUo3FF3IHTOQMMXBPicf1Hcj2I1RmdBhY";

    // Check code file existence to decide which function to call.

    if(test_file_existence("Cache/code")){
        char* codestring=read_code();
        get_authorization_code_grant_token(clientid,clientsec,codestring);

        // Must free buffer or memory will leak.

        free(codestring);
    }
    else{
        get_client_credential_token(clientid,clientsec);
    }

    LOG("Got a token and saved to Cache/token.json.\n");
}

void write_token(char* buffer){

    // Parse json response to extract token.

    cJSON* root=cJSON_Parse(buffer);
    cJSON* item=cJSON_GetObjectItem(root,"access_token");
    char* token=item->valuestring;

    // Regenerate json file including generate time and token.

    time_t current=time(NULL);
    cJSON* data=cJSON_CreateObject();
    cJSON_AddNumberToObject(data,"time",current);
    cJSON_AddStringToObject(data,"token",token);
    char* jsondata=cJSON_Print(data);

    // Simply write.

    FILE* fp;
    fp=fopen("Cache/token.json","w+");
    fprintf(fp,"%s",jsondata);
    fclose(fp);

    // Cleanup.

    cJSON_Delete(root);
}