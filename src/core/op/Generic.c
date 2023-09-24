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
        char* string=calloc(fsize,sizeof(char));
        
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

int menu_select(void){
    int select;
    printf("Type in number to select a function.\n");
    printf("1. Get Mapsets from Best Plays of anyone.\n");
    printf("0. Quit.\n");
    printf("Your selection: ");
    scanf("%d",&select);
    return select;
}

void Getbeatmapsets(const char* token){
    int* sids;
    int uid,offset,limit,mode,r;
    printf("Type in the uid you want to get bplist from: ");
    r=scanf("%d",&uid);
    if(r!=1){
        LOG("uid format error.");
        exit(16);
    }

    printf("Type in the mode of the bplist you want to get(0 stands for std, 1 for taiko, 2 for ctb, 3 for mania): ");
    r=scanf("%d",&mode);
    if((r!=1)||(mode>3)||(mode<0)){
        LOG("Mode format error.");
        exit(17);
    }

    printf("Type in the start position of the bplist you want to get(0 for default): ");
    r=scanf("%d",&offset);
    if((r!=1)||(offset>100)){
        LOG("Offset format error.");
        exit(18);
    }

    printf("Type in the end position of the bplist you want to get(100 for default): ");
    r=scanf("%d",&limit);
    if(r!=1||(limit>100)){
        LOG("Limit format error.");
        exit(19);
    }

    // Then get bplist.

    get_bplist(uid,mode,offset,limit,token);
    sids=getsids();

    // Simply download.

    mapdownloader(sids,offset,limit);
}
