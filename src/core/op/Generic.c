//
//  Mode.c
//  osu-utils
//
//  Created by Merry on 2023/9/20.
//

#include "utils/core/op/Generic.h"

char* select_mode(int mode_id){
    char* mode;
    switch(mode_id){
        case 0:
            mode="osu";
            break;
        case 1:
            mode="taiko";
            break;
        case 2:
            mode="fruits";
            break;
        case 3:
            mode="mania";
            break;
        default:
            LOG("Mode error.\n");
            exit(-4);
            break;
    }
    return mode;
}

bool test_file_existence(char* path){
    bool flag=false;
    if(access(path,F_OK)==0){
        flag=true;
    }
    return flag;
}

char* read_file(const char* path){
    FILE* fp=fopen(path,"r");
    if(fp){

        // Make full use of memory from malloc.

        fseek(fp,0,SEEK_END);
        size_t fsize=ftell(fp);
        char* string=malloc(fsize*sizeof(fsize));
        
        // Simply read the file, regardless of anything.

        fseek(fp,0,SEEK_SET);
        char ch;
        char* ptr=string;
        while(!feof(fp)){
            ch=fgetc(fp);
            * ptr++=ch;
        }
        fclose(fp);
        return string;
    }
    else{
        
        // It's impossible, isn't it.

        LOG("Failed to create a file pointer.\n");
        exit(128);
    }
}