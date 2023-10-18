#include "utils/extra/score/Analyze.h"

void score_analyze(struct personal_info info,char* score_list){

    struct ranking_analyze statistics={0};

    cJSON* mod_intro_statistics=cJSON_CreateObject();
    cJSON* root=cJSON_Parse(score_list);
    int arraysize=cJSON_GetArraySize(root);

    for(int i=0;i<arraysize;i++){

        cJSON* score_info=cJSON_GetArrayItem(root,i);

        // Get username.

        if(!i){
            cJSON* user=cJSON_GetObjectItem(score_info,"user");
            cJSON* username=cJSON_GetObjectItem(user,"username");
            printf("%s [%s]\n",username->valuestring,osu_mode_Strings[info.mode]);
        }

        // Parsing.

        cJSON* pp=cJSON_GetObjectItem(score_info,"pp");
        cJSON* rank=cJSON_GetObjectItem(score_info,"rank");
        cJSON* perfect_flag=cJSON_GetObjectItem(score_info,"perfect");
        cJSON* mods=cJSON_GetObjectItem(score_info,"mods");

        bool flag=perfect_flag->valueint;
        char* ranking=rank->valuestring;
        int mod_sum=cJSON_GetArraySize(mods);

        // Get Mod intro count.

        for(int k=0;k<mod_sum;k++){
            cJSON* mod=cJSON_GetArrayItem(mods,k);
            if(cJSON_HasObjectItem(mod_intro_statistics,mod->valuestring)==0){
                cJSON_AddNumberToObject(mod_intro_statistics,mod->valuestring,1);
            }
            else{
                cJSON* num=cJSON_GetObjectItem(mod_intro_statistics,mod->valuestring);
                int number=num->valueint;
                number++;
                cJSON_SetNumberValue(num,number);
            }
        }

        // Get ppmax and ppmin.

        if(!i){
            statistics.ppmax=pp->valuedouble;
        }
        if(i==arraysize-1){
            statistics.ppmin=pp->valuedouble;
        }

        // Print first 5 and last 5 while accumulating related data.

        if((i<5)||(i>=arraysize-5)){
            size_t score_id;
            cJSON* best_id=cJSON_GetObjectItem(score_info,"best_id");
            cJSON* acc=cJSON_GetObjectItem(score_info,"accuracy");
            score_id=cJSON_GetNumberValue(best_id);

            // Get Mods applied.
            
            char* mods_string=strf_mod_intro(mods);

            printf("#%d %.2f %.2f%% %s%shttps://osu.ppy.sh/scores/%s/%ld\n",(i+1),pp->valuedouble,100*acc->valuedouble,ranking,mods_string,osu_mode_Strings[info.mode],score_id);
            
            // Clean up.

            free(mods_string);
        }

        // Accumulate.

        statistics.avgpp+=pp->valuedouble;

        if(flag){
            statistics.fc++;
        }
        if(strcmp(ranking,"S")==0){
            statistics.s++;
        }
        if(strcmp(ranking,"SH")==0){
            statistics.sh++;
        }
        if(strcmp(ranking,"X")==0){
            statistics.x++;
        }
        if(strcmp(ranking,"XH")==0){
            statistics.xh++;
        }
    }
    
    statistics.avgpp/=arraysize;

    // Mod Intro.

    printf("Mod Introduction: \n");
    cJSON* now=mod_intro_statistics->child;
    while(now!=NULL){
        char* key=now->string;
        int value=now->valueint;
        printf("%s: %d; ",key,value);
        now=now->next;
    }
    printf("\n");
    
    // Misc informations.

    printf("There are %d S ranks or above in your bplist.\n",(statistics.s+statistics.sh+statistics.x+statistics.xh));
    printf("There are %d FC in your bplist.\n",statistics.fc);
    printf("There are %d SS ranks in your bplist.\n",(statistics.x+statistics.xh));
    printf("The range of your bplist is %.2f.\n",(statistics.ppmax-statistics.ppmin));
    printf("The average pp of the scores on your bplist is %.2f.\n",statistics.avgpp);

    // Cleanup.

    cJSON_Delete(root);
    cJSON_Delete(mod_intro_statistics);
}
