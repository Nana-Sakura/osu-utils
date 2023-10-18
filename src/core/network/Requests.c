#include "utils/core/network/Requests.h"

size_t cb(char* buffer,size_t size,size_t nitems,void* userdata){
    size_t realsize=size*nitems;
    struct memory* mem=(struct memory*) userdata;
    char* ptr=realloc(mem->response,mem->size+realsize+1);
    if(buffer==NULL){
        LOG("Out Of Memory Exception.");
        exit(16);
    }
    mem->response=ptr;
    memcpy(&(mem->response[mem->size]),buffer,realsize);
    mem->size+=realsize;
    mem->response[mem->size]=0;
    return realsize;
}

char* curl_get_request(const char* path_to_source,const char* token){
    CURL* eh=curl_easy_init();
    if(eh){
        char oauth[1500]={'\0'};
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
        LOG("Null Pointer Exception.");
        exit(16);
    }
}

char* curl_post_request(const char* data_to_post){

    // Specified for getting token.

    CURL* eh=curl_easy_init();
    if(eh){
        struct memory chunk={0};
        struct curl_slist* list;        
        list=curl_slist_append(NULL,"Accept: application/json");
        list=curl_slist_append(list,"Content-Type: application/x-www-form-urlencoded");
        curl_easy_setopt(eh,CURLOPT_URL,"https://osu.ppy.sh/oauth/token");
        curl_easy_setopt(eh,CURLOPT_HTTPHEADER,list);
        curl_easy_setopt(eh,CURLOPT_POSTFIELDSIZE,(long)strlen(data_to_post));
        curl_easy_setopt(eh,CURLOPT_POSTFIELDS,data_to_post);
        curl_easy_setopt(eh,CURLOPT_WRITEFUNCTION,cb);
        curl_easy_setopt(eh,CURLOPT_WRITEDATA,(void*) &chunk);
        curl_easy_setopt(eh,CURLOPT_TIMEOUT,30);
        curl_easy_perform(eh);
        curl_easy_cleanup(eh);
        return chunk.response;
    }
    else{
        LOG("Null Pointer Exception.");
        exit(16);
    }
}

char* curl_get_object_request(const char* path_to_source){
    CURL* eh=curl_easy_init();
    if(eh){
        struct memory chunk={0};
        curl_easy_setopt(eh,CURLOPT_URL,path_to_source);
        curl_easy_setopt(eh,CURLOPT_FOLLOWLOCATION,1);
        curl_easy_setopt(eh,CURLOPT_WRITEFUNCTION,cb);
        curl_easy_setopt(eh,CURLOPT_WRITEDATA,(void*) &chunk);
        curl_easy_perform(eh);
        curl_easy_cleanup(eh);
        return chunk.response;
    }
    else{
        LOG("Null Pointer Exception.");
        exit(16);
    }    
}
