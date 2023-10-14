//
//  Downloader.c
//  osu-utils
//
//  Created by Merry on 2023/9/20.
//

#include "utils/core/network/Downloader.h"

int compare(const void* p1,const void* p2){
    return (*(int*) p1)-(*(int*) p2);
}

void mapdownloader(char* bplist,int offset,int limit){

    // Do prepare jobs.

    if(!bplist){
        LOG("Bplist is empty, maybe network error.");
        exit(-7);
    }
    
    cJSON* root=cJSON_Parse(bplist);

    // Must free buffer or memory will leak.

    free(bplist);

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


    struct stat st={0};
    if(stat("Mapsets",&st)==-1){
        mkdir("Mapsets",0755);
    }

    //To make life easier, sort the items before removing the duplicated.
    
    int j=1,count;
    qsort(array,arraysize,sizeof(int),compare);
    for(int i=1;i<limit-offset;i++){
        if(array[i]!=array[i-1]){
            array[j++]=array[i];
        }
    }
    count=j;
    
    // TODO: curl_multi
    // It's working well now. If needed, will do multi.
    
    CURL* downloader;
    
    for(int i=0;i<count;i++){

        // Show Progress.
        
        show_progress(i,count,70);

        // Download Progress.

        downloader=curl_easy_init();
        if(downloader){
            struct memory chunk={0};
            char url[60];
            sprintf(url,"https://dl.sayobot.cn/beatmaps/download/full/%d",array[i]);
            curl_easy_setopt(downloader,CURLOPT_URL,url);
            curl_easy_setopt(downloader,CURLOPT_FOLLOWLOCATION,1);
            curl_easy_setopt(downloader,CURLOPT_WRITEFUNCTION,cb);
            curl_easy_setopt(downloader,CURLOPT_WRITEDATA,(void*) &chunk);
            curl_easy_perform(downloader);
            FILE* fp;
            char fname[20];
            sprintf(fname,"Mapsets/%d.osz",array[i]);
            fp=fopen(fname,"wb");
            fwrite(chunk.response,sizeof(char),chunk.size,fp);
            fclose(fp);
            free(chunk.response);
            curl_easy_cleanup(downloader);
        }
    }
    show_progress(count,count,70);
    printf("\n");
}
