//
//  Getbplist.c
//  osu-utils
//
//  Created by Merry on 2023/9/20.
//

#include "utils/core/network/Getbplist.h"

char* get_bplist(int uid,int mode_id,int offset,int limit,const char* token){
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
        curl_easy_cleanup(eh);

        // Directly return bplist other than write to file.

        return chunk.response;
    }
    else{
        LOG("Failed to get bplist.");
        exit(16);
    }
}
