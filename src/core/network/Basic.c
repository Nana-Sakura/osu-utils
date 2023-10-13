//
//  Basic.c
//  osu-utils
//
//  Created by Merry on 2023/9/20.
//

#include "utils/core/network/Basic.h"

size_t cb(char* buffer,size_t size,size_t nitems,void* userdata){
    size_t realsize=size*nitems;
    struct memory* mem=(struct memory*) userdata;
    char* ptr=realloc(mem->response,mem->size+realsize+1);
    if(buffer==NULL){
        LOG("Out of memory.");
        exit(2);
    }
    mem->response=ptr;
    memcpy(&(mem->response[mem->size]),buffer,realsize);
    mem->size+=realsize;
    mem->response[mem->size]=0;
    return realsize;
}

char* curl_request(const char* path_to_source,const char* token){
    CURL* eh=curl_easy_init();
    if(eh){
        char oauth[1050];
        struct curl_slist* list;
        struct memory chunk={0};
        sprintf(oauth,"Authorization: Bearer %s",token);
        list=curl_slist_append(NULL,"Content-Type: application/json");
        list=curl_slist_append(list,"Accept: application/json");
        list=curl_slist_append(list,oauth);
        curl_easy_setopt(eh,CURLOPT_URL,path_to_source);
        curl_easy_setopt(eh,CURLOPT_HTTPHEADER,list);
        curl_easy_setopt(eh,CURLOPT_WRITEFUNCTION,cb);
        curl_easy_setopt(eh,CURLOPT_WRITEDATA,(void*) &chunk);
        curl_easy_setopt(eh,CURLOPT_TIMEOUT,30);
        curl_easy_perform(eh);
        curl_easy_cleanup(eh);

        // Directly return response other than write to file.

        return chunk.response;
    }
    else{
        LOG("Failed to get score.");
        exit(16);
    }
}
