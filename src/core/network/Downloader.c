//
//  Downloader.c
//  osu-utils
//
//  Created by Merry on 2023/9/20.
//

#include "Downloader.h"

int compare(const void* p1,const void* p2){
    return (*(int*) p1)-(*(int*) p2);
}

void mapdownloader(int* sids,int offset,int limit){
    struct stat st={0};
    if(stat("Mapsets",&st)==-1){
        mkdir("Mapsets",0755);
    }
    //To make life easier, sort the items before removing the duplicated.
    int j=1,count;
    qsort(sids,limit-offset,sizeof(int),compare);
    for(int i=1;i<limit-offset;i++){
        if(sids[i]!=sids[i-1]){
            sids[j++]=sids[i];
        }
    }
    count=j;
    
    // TODO: curl_multi
    // It's working well now. If needed, will do multi.
    
    CURL* downloader;
    
    for(int i=0;i<count;i++){
        downloader=curl_easy_init();
        if(downloader){
            struct memory chunk={0};
            char url[60];
            sprintf(url,"https://dl.sayobot.cn/beatmaps/download/full/%d",sids[i]);
            curl_easy_setopt(downloader,CURLOPT_URL,url);
            curl_easy_setopt(downloader,CURLOPT_FOLLOWLOCATION,1);
            curl_easy_setopt(downloader,CURLOPT_WRITEFUNCTION,cb);
            curl_easy_setopt(downloader,CURLOPT_WRITEDATA,(void*) &chunk);
            curl_easy_perform(downloader);
            FILE* fp;
            char fname[20];
            sprintf(fname,"Mapsets/%d.osz",sids[i]);
            fp=fopen(fname,"wb");
            fwrite(chunk.response,sizeof(char),chunk.size,fp);
            fclose(fp);
            free(chunk.response);
            curl_easy_cleanup(downloader);
        }
    }
}
