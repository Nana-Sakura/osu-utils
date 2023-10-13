//
//  Generic.c
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

char* select_check_mode(int check_mode_id){
    char* mode;
    switch(check_mode_id){
        case 0:
            mode="best";
            break;
        case 1:
            mode="recent";
            break;
        case 2:
            mode="firsts";
            break;
        default:
            LOG("Mode format error.\n");
            exit(16);
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
    printf("\n");
    printf("Type in number to select a function.\n");
    printf("1. Get Mapsets from Best Plays of anyone.\n");
    printf("2. Get Bpht of anyone.\n");
    printf("3. Get Bpht of yourself.\n");
    printf("4. Get Score of a specified beatmap of anyone.\n");
    printf("5. Get Score of a specified beatmap of yourself.\n");
    printf("6. Get Score of your recently passed beatmap.\n");
    printf("7. Get Score of other's recently passed beatmap.\n");
    printf("8. Get Score of your recently played beatmap.\n");
    printf("9. Get Score of other's recently played beatmap.\n");
    printf("10.Calculate pp of any beatmap.(Currently mania only)\n");
    printf("99.Set your ID and default game mode.\n");
    printf("0. Quit.\n");
    printf("Your selection: ");
    scanf("%d",&select);
    printf("\n");
    return select;
}

void get_beatmapsets(const char* token){
    int uid,offset,limit,mode,r;
    char* bplist;

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
        exit(16);
    }

    printf("Type in the start position of the bplist you want to get(0 for default): ");
    r=scanf("%d",&offset);
    if((r!=1)||(offset>100)){
        LOG("Offset format error.");
        exit(16);
    }

    printf("Type in the end position of the bplist you want to get(100 for default): ");
    r=scanf("%d",&limit);
    if(r!=1||(limit>100)){
        LOG("Limit format error.");
        exit(16);
    }

    // Then get bplist.

    bplist=get_score_list(uid,mode,offset,limit,0,0,token);

    // Simply download.

    mapdownloader(bplist,offset,limit);
}

void Bpa(int check_mode,const char* token){
    struct personal_info i=get_info(check_mode);
    Getbpht(i.uid,i.mode,token);
}

void Setid(void){
    int r,uid,mode;

    printf("Type in your uid: ");
    r=scanf("%d",&uid);
    if(r!=1){
        LOG("uid format error.");
        exit(16);
    }

    printf("Type in the mode you aimed at(0 stands for std, 1 for taiko, 2 for ctb, 3 for mania): ");
    r=scanf("%d",&mode);
    if((r!=1)||(mode>3)||(mode<0)){
        LOG("Mode format error.");
        exit(16);
    }

    cJSON* info=cJSON_CreateObject();
    cJSON_AddNumberToObject(info,"uid",uid);
    cJSON_AddNumberToObject(info,"mode",mode);
    char* json=cJSON_Print(info);
    FILE* fp=fopen("Cache/user.json","w+");
    fprintf(fp,"%s",json);
    fclose(fp);

    cJSON_Delete(info);
}

char* mod_intro(cJSON* mods){
    int mod_sum=cJSON_GetArraySize(mods);
    char* mods_string=malloc((3*mod_sum+2)*sizeof(char));
    if(mod_sum==0){
        strcpy(mods_string," ");
    }
    else{
        mods_string[0]='+';
        for(int j=0;j<mod_sum;j++){
            cJSON* mod=cJSON_GetArrayItem(mods,j);
            strcat(mods_string,mod->valuestring);
            mods_string[3*(j+1)]=' ';
        }
    }
    return mods_string;
}

void score(int info_get_mode,const char* token){

    // Get info.

    cJSON* root=NULL;
    struct personal_info i=get_info(info_get_mode);

    // Get score and beatmap info.

    int beatmap_id,r;

    printf("Type in the id of the beatmap(bid): ");
    r=scanf("%d",&beatmap_id);
    if((r==0)||(beatmap_id<=0)){
        LOG("BID format error.");
        return;
    }
    char* score=get_beatmap_score(i.uid,i.mode,beatmap_id,token);
    char* info=get_beatmap_info(beatmap_id,token);

    // Parse and output.

    get_score(score,info);

    // Clean up.

    // Avoid freeing non-heap memory.

    if(info_get_mode){
        cJSON_Delete(root);
    }

    free(score);
    free(info);
}

void recent(int score_request_mode,int info_get_mode,int include_fails,const char* token){
    struct personal_info i=get_info(info_get_mode);
    char* score=get_score_list(i.uid,i.mode,0,1,score_request_mode,include_fails,token);
    get_recent(score,token);
    
    free(score);
}

struct personal_info get_info(int check_mode){
    struct personal_info result;
    cJSON* root;
    if(check_mode){
        if(!test_file_existence("Cache/user.json")){
            LOG("You haven't set your ID and default mode.");
            exit(16);
        }
        char* me=read_file("Cache/user.json");
        root=cJSON_Parse(me);
        free(me);
        cJSON* uid_object=cJSON_GetObjectItem(root,"uid");
        result.uid=uid_object->valueint;
        cJSON* mode_object=cJSON_GetObjectItem(root,"mode");
        result.mode=mode_object->valueint;
        cJSON_Delete(root);
    }
    else{
        int r;
        printf("Type in the uid you want to score from: ");
        r=scanf("%d",&result.uid);
        if(r!=1){
            LOG("uid format error.");
            exit(16);
        }

        printf("Type in the mode of the score you want to get(0 stands for std, 1 for taiko, 2 for ctb, 3 for mania): ");
        r=scanf("%d",&result.mode);
        if((r!=1)||(result.mode>3)||(result.mode<0)){
            LOG("Mode format error.");
            exit(16);
        }
    }

    return result;
}

char* strfsec(int length){
    if((length>=86400)||(length<=0)){
        LOG("The beatmap is not aimed for humans.\n");
        exit(16);
    }
    int hrs=length/3600;
    length%=3600;
    int min=length/60;
    length%=60;
    int vaild_num=3;
    if(hrs==0){
        vaild_num--;
    }
    char* result=malloc(vaild_num*3*sizeof(char));
    if(vaild_num==3){
        sprintf(result,"%d:%02d:%02d",hrs,min,length);
    }
    else{
        sprintf(result,"%d:%02d",min,length);
    }
    return result;
}

void calc_mania_pp(void){
    struct statistics_mania i;
    int r,ez,nf;

    printf("Type in the count of rainbow 300: ");
    r=scanf("%u",&i.perfect);
    if((r==0)||(i.perfect<0)){
        LOG("Format error.");
        return;
    }

    printf("Type in the count of yellow 300: ");
    r=scanf("%u",&i.great);
    if((r==0)||(i.great<0)){
        LOG("Format error.");
        return;
    }

    printf("Type in the count of 200: ");
    r=scanf("%u",&i.good);
    if((r==0)||(i.good<0)){
        LOG("Format error.");
        return;
    }

    printf("Type in the count of 100: ");
    r=scanf("%u",&i.ok);
    if((r==0)||(i.ok<0)){
        LOG("Format error.");
        return;
    }

    printf("Type in the count of 50: ");
    r=scanf("%u",&i.meh);
    if((r==0)||(i.meh<0)){
        LOG("Format error.");
        return;
    }

    printf("Type in the count of miss: ");
    r=scanf("%u",&i.miss);
    if((r==0)||(i.miss<0)){
        LOG("Format error.");
        return;
    }

    printf("Type in the Star Rating of the beatmap: ");
    r=scanf("%f",&i.sr);
    if((r==0)||(i.sr<0)){
        LOG("Format error.");
        return;
    }

    printf("Type in the if you have applied EZ mod(0 stands for no, 1 for yes): ");
    r=scanf("%d",&ez);
    if((r==0)||(ez<0)||(ez>1)){
        LOG("Format error.");
        return;
    }

    printf("Type in the if you have applied NF mod(0 stands for no, 1 for yes): ");
    r=scanf("%d",&nf);
    if((r==0)||(nf<0)||(nf>1)){
        LOG("Format error.");
        return;
    }

    cJSON* mods=cJSON_CreateArray();
    if(ez){
        cJSON* ez_obj=cJSON_CreateString("EZ");
        cJSON_AddItemToArray(mods,ez_obj);
    }
    if(nf){
        cJSON* nf_obj=cJSON_CreateString("NF");
        cJSON_AddItemToArray(mods,nf_obj);
    }

    mania_pp(i,mods);
    
    cJSON_Delete(mods);
}