//
//  OAuth.c
//  osu-utils
//
//  Created by Merry on 2023/9/20.
//

#include "utils/core/auth/OAuth.h"

void read_token(char* tokenstring,int fails){
    FILE* fp=fopen("Cache/token.json","r");
    if(fp){
        fseek(fp,0,SEEK_END);
        long fsize=ftell(fp);
        if(fsize==0){
            on_token_expire();
            exit(-1);
        }
        fseek(fp,0,SEEK_SET);
        char ch;
        char* string=(char*) malloc(fsize);
        char* ptr=string;
        while(!feof(fp)){
            ch=fgetc(fp);
            * ptr++=ch;
        }
        fclose(fp);
        cJSON* root=cJSON_Parse(string);
        free(string);
        cJSON* timethen=cJSON_GetObjectItem(root,"time");
        time_t previous_time=timethen->valueint;
        time_t current_time=time(NULL);
        if(current_time-previous_time>=86400){
            on_token_expire();
            exit(-2);
        }
        cJSON* token=cJSON_GetObjectItem(root,"token");
        sprintf(tokenstring,"%s",token->valuestring);
        cJSON_Delete(root);
    }
    else{
        fails++;
        if(fails>1){
            LOG("Failed to read and get token.\n");
        }
        on_token_expire();
        read_token(tokenstring,fails);
    }
}

void on_token_expire(void){
    LOG("Failed to read token, will get another.\n");
//    int clientid=5;
//    char* clientsec="FGc9GAtyHzeQDshWP5Ah7dega8hJACAJpQtw6OXk";
    int clientid=24548;
    char* clientsec="8ZNaZq1uUo3FF3IHTOQMMXBPicf1Hcj2I1RmdBhY";
    get_token(clientid,clientsec);
}

void get_token(int clientid,const char* clientsec){
    CURL* eh=curl_easy_init();
    if(eh){
        struct curl_slist* list;
        char data[114];
        sprintf(data,"client_id=%d&client_secret=%s&grant_type=client_credentials&scope=public",clientid,clientsec);
        list=curl_slist_append(NULL,"Accept: application/json");
        list=curl_slist_append(list,"Content-Type: application/x-www-form-urlencoded");
        curl_easy_setopt(eh,CURLOPT_URL,"https://osu.ppy.sh/oauth/token");
        curl_easy_setopt(eh,CURLOPT_PROXY,"http://localhost:7890");
        curl_easy_setopt(eh,CURLOPT_HTTPHEADER,list);
        curl_easy_setopt(eh,CURLOPT_POSTFIELDSIZE,(long)strlen(data));
        curl_easy_setopt(eh,CURLOPT_POSTFIELDS,data);
        curl_easy_setopt(eh,CURLOPT_TIMEOUT,30);
        curl_easy_setopt(eh,CURLOPT_WRITEFUNCTION,token_cb);
        curl_easy_perform(eh);
        curl_easy_cleanup(eh);
    }
    else{
        LOG("Failed to get token.\n");
        exit(1);
    }
}

size_t token_cb(char* buffer,size_t size,size_t nitems,void* userdata){
    FILE* read=(FILE*) userdata;
    size_t retcode=fread(buffer,size,nitems,read);
    cJSON* root=cJSON_Parse(buffer);
    cJSON* item=cJSON_GetObjectItem(root,"access_token");
    char* token=item->valuestring;
    time_t current=time(NULL);
    cJSON* data=cJSON_CreateObject();
    cJSON_AddNumberToObject(data,"time",current);
    cJSON_AddStringToObject(data,"token",token);
    char* jsondata=cJSON_Print(data);
    FILE* fp;
    fp=fopen("Cache/token.json","w+");
    fprintf(fp,"%s",jsondata);
    fclose(fp);
    cJSON_Delete(root);
    return retcode;
}
