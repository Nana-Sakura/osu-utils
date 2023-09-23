//
//  Getbplist.c
//  osu-utils
//
//  Created by Merry on 2023/9/20.
//

#include "utils/core/network/Getbplist.h"

void get_bplist(int uid,uint8_t mode_id,int offset,int limit,const char* token){
    CURL* eh=curl_easy_init();
    if(eh){
        char* mode=select_mode(mode_id);
        char url[114];
        char oauth[1050];
        struct curl_slist* list;
        struct memory chunk={0};
        sprintf(url,"https://osu.ppy.sh/api/v2/users/%d/scores/best?include_fails=0&mode=%s&limit=%d&offset=%d",uid,mode,limit,offset);
        sprintf(oauth,"Authorization: Bearer %s",token);
        list=curl_slist_append(NULL,"Content-Type: application/json");
        list=curl_slist_append(list,"Accept: application/json");
        list=curl_slist_append(list,oauth);
        curl_easy_setopt(eh,CURLOPT_URL,url);
        curl_easy_setopt(eh,CURLOPT_HTTPHEADER,list);
        curl_easy_setopt(eh,CURLOPT_WRITEFUNCTION,cb);
        curl_easy_setopt(eh,CURLOPT_WRITEDATA,(void*) &chunk);
        curl_easy_setopt(eh,CURLOPT_TIMEOUT,30);
        curl_easy_perform(eh);
        
        // Write bplist to file.
        
        FILE* fp;
        fp=fopen("Cache/bplist.json","w+");
        fprintf(fp,"%s",chunk.response);
        fclose(fp);
        
        free(chunk.response);
        curl_easy_cleanup(eh);
    }
    else{
        LOG("Failed to get bplist.\n");
    }
}

int* getsids(void){
    char* buffer;
    buffer=read_file("Cache/bplist.json");
    if(buffer){
        cJSON* root=cJSON_Parse(buffer);

        // Must free buffer or memory will leak.

        free(buffer);

        int arraysize=cJSON_GetArraySize(root);
        cJSON* info;
        cJSON* beatmap;
        cJSON* siditem;
        int sid;
        int* array=(int*) malloc(arraysize*sizeof(int));
        for(int i=0;i<arraysize;i++){
            info=cJSON_GetArrayItem(root,i);
            beatmap=cJSON_GetObjectItem(info,"beatmap");
            siditem=cJSON_GetObjectItem(beatmap,"beatmapset_id");
            sid=siditem->valueint;
            array[i]=sid;
        }
        cJSON_Delete(root);
        return array;
    }
    else{
        LOG("File is empty, maybe network error.\n");
        exit(-7);
    }
}
