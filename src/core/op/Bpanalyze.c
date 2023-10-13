//
//  Bpanalyze.c
//  osu-utils
//
//  Created by Merry on 2023/9/20.
//

#include "utils/core/op/Bpanalyze.h"

void Getbpht(int uid,int mode,const char* token){

    char* bplist;
    bplist=get_score_list(uid,mode,0,100,0,0,token);

    // Start the work.

    cJSON* info;
    cJSON* acc,* best_id,* mods,* perfect_flag,* pp,* rank,* user,* username;
    int s=0,sh=0,x=0,xh=0,fc=0,mod_sum;
    float avgpp=0,ppmax,ppmin;
    char* rank_value;
    bool flag;
    
    cJSON* mod_statistics;
    mod_statistics=cJSON_CreateObject();

    cJSON* root=cJSON_Parse(bplist);
    int arraysize=cJSON_GetArraySize(root);

    for(int i=0;i<arraysize;i++){
        info=cJSON_GetArrayItem(root,i);

        // Get username.

        if(!i){
            user=cJSON_GetObjectItem(info,"user");
            username=cJSON_GetObjectItem(user,"username");
            printf("%s [%s]\n",username->valuestring,select_mode(mode));
        }
        
        // Other stuff.

        pp=cJSON_GetObjectItem(info,"pp");
        rank=cJSON_GetObjectItem(info,"rank");
        perfect_flag=cJSON_GetObjectItem(info,"perfect");
        mods=cJSON_GetObjectItem(info,"mods");

        flag=perfect_flag->valueint;
        rank_value=rank->valuestring;

        if(mods->type!=cJSON_Array){
            LOG("Failed to parse bplist.");
            exit(144);
        }
        mod_sum=cJSON_GetArraySize(mods);

        for(int k=0;k<mod_sum;k++){
            cJSON* mod=cJSON_GetArrayItem(mods,k);
            if(cJSON_HasObjectItem(mod_statistics,mod->valuestring)==0){
                cJSON_AddNumberToObject(mod_statistics,mod->valuestring,1);
            }
            else{
                cJSON* num=cJSON_GetObjectItem(mod_statistics,mod->valuestring);
                int number=num->valueint;
                number++;
                cJSON_SetNumberValue(num,number);
            }
        }

        // Get ppmax and ppmin.

        if(!i){
            ppmax=pp->valuedouble;
        }

        if(i==arraysize-1){
            ppmin=pp->valuedouble;
        }

        // Print first 5 and last 5 while accumulating related data.

        if((i<5)||(i>=arraysize-5)){
            size_t scoreid;
            best_id=cJSON_GetObjectItem(info,"best_id");
            acc=cJSON_GetObjectItem(info,"accuracy");
            scoreid=cJSON_GetNumberValue(best_id);

            // Get Mods applied.
            
            char* mods_string=mod_intro(mods);

            printf("#%d %.2f %.2f%% %s%shttps://osu.ppy.sh/scores/%s/%ld\n",(i+1),pp->valuedouble,100*acc->valuedouble,rank_value,mods_string,select_mode(mode),scoreid);
            
            // Clean up.

            free(mods_string);
        }

        // Accumulate.

        avgpp+=pp->valuedouble;

        if(flag){
            fc++;
        }
        if(strcmp(rank_value,"S")==0){
            s++;
        }
        if(strcmp(rank_value,"SH")==0){
            sh++;
        }
        if(strcmp(rank_value,"X")==0){
            x++;
        }
        if(strcmp(rank_value,"XH")==0){
            xh++;
        }
        
    }
    
    avgpp/=arraysize;

    // Mod Intro.

    printf("Mod Introduction: \n");
    cJSON* now=mod_statistics->child;
    while(now!=NULL){
        char* key=now->string;
        int value=now->valueint;
        printf("%s: %d; ",key,value);
        now=now->next;
    }
    printf("\n");
    
    // Misc informations.

    printf("There are %d S ranks or above in your bplist.\n",(s+sh+x+xh));
    printf("There are %d FCs in your bplist.\n",fc);
    printf("There are %d SS ranks in your bplist.\n",(x+xh));
    printf("The range of your bplist is %.2f.\n",(ppmax-ppmin));
    printf("The average pp of the scores on your bplist is %.2f.\n",avgpp);

    // Cleanup.

    cJSON_Delete(root);
    cJSON_Delete(mod_statistics);
    free(bplist);
}
