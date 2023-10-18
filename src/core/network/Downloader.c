#include "utils/core/network/Downloader.h"

int compare(const void* p1,const void* p2){
    return (*(int*) p1)-(*(int*) p2);
}

void map_downloader(char* score_list,int offset,int limit){

    // Do prepare jobs.

    if(!score_list){
        LOG("Bplist is empty, maybe network error.");
        exit(16);
    }
    
    cJSON* root=cJSON_Parse(score_list);
    int arraysize=cJSON_GetArraySize(root);
    int* array=(int*) malloc(arraysize*sizeof(int));
    
    for(int i=0;i<arraysize;i++){
        cJSON* info=cJSON_GetArrayItem(root,i);
        cJSON* beatmap=cJSON_GetObjectItem(info,"beatmap");
        cJSON* siditem=cJSON_GetObjectItem(beatmap,"beatmapset_id");
        array[i]=siditem->valueint;
    }
    
    cJSON_Delete(root);

    // Will write data to Mapsets Folder.

    if(get_file_size("Mapsets")==-1){
        mkdir("Mapsets",0755);
    }

    // To make life easier, sort the items before removing the duplicated.
    
    int j=1,count;
    qsort(array,arraysize,sizeof(int),compare);
    for(int i=1;i<limit-offset;i++){
        if(array[i]!=array[i-1]){
            array[j++]=array[i];
        }
    }
    count=j;
    
    // TODO: curl_multi or pthread
    // It's working well now. If needed, will do multi.
    
    for(int i=0;i<count;i++){

        // Show Progress.
        
        show_progress(i,count,70);

        // Download Progress.

        char url[60];
        sprintf(url,"https://dl.sayobot.cn/beatmaps/download/full/%d",array[i]);
        char* beatmap_object=curl_get_object_request(url);
        char path[50];
        sprintf(path,"Mapsets/%d.osz",array[i]);
        write_file(path,beatmap_object,"wb");
        
        // Cleanup.

        free(beatmap_object);

    }

    show_progress(count,count,70);
    printf("\n");

    // Cleanup.
    
    free(array);
}
