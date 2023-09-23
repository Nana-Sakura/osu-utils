//
//  Basic.c
//  osu-utils
//
//  Created by Merry on 2023/9/20.
//

#include "utils/core/network/Basic.h"

size_t cb(char* buffer,size_t size,size_t nitems,void* userdata){
    size_t realsize=size*nitems;
    struct memory *mem=(struct memory*) userdata;
    char* ptr=realloc(mem->response,mem->size+realsize+1);
    if(buffer==NULL){
        LOG("Out of memory.\n");
        exit(2);
    }
    mem->response=ptr;
    memcpy(&(mem->response[mem->size]),buffer,realsize);
    mem->size+=realsize;
    mem->response[mem->size]=0;
    return realsize;
}
