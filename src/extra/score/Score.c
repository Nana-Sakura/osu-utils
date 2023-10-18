#include "utils/extra/score/Score.h"

void get_score(char* beatmap_score,char* beatmap_info){

    // Parsing from first json respond.

    cJSON* root=cJSON_Parse(beatmap_score);
    cJSON* score=cJSON_GetObjectItem(root,"score");
    cJSON* user=cJSON_GetObjectItem(score,"user");
    cJSON* username=cJSON_GetObjectItem(user,"username");
    cJSON* country_code=cJSON_GetObjectItem(user,"country_code");
    cJSON* beatmap=cJSON_GetObjectItem(score,"beatmap");
    cJSON* mode=cJSON_GetObjectItem(beatmap,"mode");
    cJSON* diff=cJSON_GetObjectItem(beatmap,"version");
    cJSON* sr=cJSON_GetObjectItem(beatmap,"difficulty_rating");
    cJSON* length=cJSON_GetObjectItem(beatmap,"hit_length");
    cJSON* bid=cJSON_GetObjectItem(beatmap,"id");
    cJSON* rank=cJSON_GetObjectItem(score,"rank");
    cJSON* mods=cJSON_GetObjectItem(score,"mods");
    cJSON* score_value=cJSON_GetObjectItem(score,"score");
    cJSON* pp=cJSON_GetObjectItem(score,"pp");
    cJSON* combo=cJSON_GetObjectItem(score,"max_combo");
    cJSON* accuracy=cJSON_GetObjectItem(score,"accuracy");
    cJSON* statistics=cJSON_GetObjectItem(score,"statistics");
    cJSON* geki=cJSON_GetObjectItem(statistics,"count_geki");
    cJSON* great=cJSON_GetObjectItem(statistics,"count_300");
    cJSON* katu=cJSON_GetObjectItem(statistics,"count_katu");
    cJSON* ok=cJSON_GetObjectItem(statistics,"count_100");
    cJSON* meh=cJSON_GetObjectItem(statistics,"count_50");
    cJSON* miss=cJSON_GetObjectItem(statistics,"count_miss");
    
    // Another.

    cJSON* info=cJSON_Parse(beatmap_info);
    cJSON* beatmapset=cJSON_GetObjectItem(info,"beatmapset");
    cJSON* artist=cJSON_GetObjectItem(beatmapset,"artist");
    cJSON* title=cJSON_GetObjectItem(beatmapset,"title");
    cJSON* full_combo=cJSON_GetObjectItem(info,"max_combo");

    // Format time pattern.

    char* length_str=strfsec(length->valueint);

    // Mod introduction.

    char* mod_introed=strf_mod_intro(mods);

    // osu!mania specifies.

    int flag=strcmp(mode->valuestring,"mania");

    if(!flag){
        cJSON* cs=cJSON_GetObjectItem(beatmap,"cs");
        printf("%s (%s): %s (%dK)\n",username->valuestring,country_code->valuestring,mode->valuestring,cs->valueint);
    }
    else{
        printf("%s (%s): %s\n",username->valuestring,country_code->valuestring,mode->valuestring);
    }
    printf("%s - %s [%s]\n",artist->valuestring,title->valuestring,diff->valuestring);
    printf("%.2f* %s\n",sr->valuedouble,length_str);
    printf("[%s]%s%d (%.3fpp)\n",rank->valuestring,mod_introed,score_value->valueint,pp->valuedouble);
    printf("%dx / %dx // %.3f%%\n",combo->valueint,full_combo->valueint,100*accuracy->valuedouble);
    
    // osu!mania specifies.

    if(!flag){
        float precision=geki->valuedouble/great->valuedouble;
        printf("%d+%d(%.1f) / %d / %d / %d / %d\n",great->valueint,geki->valueint,precision,katu->valueint,ok->valueint,meh->valueint,miss->valueint);
    }
    else{
        printf("%d / %d / %d / %d\n",great->valueint,ok->valueint,meh->valueint,miss->valueint);
    }

    // Provide beatmap URL.

    printf("https://osu.ppy.sh/b/%d\n",bid->valueint);

    // Clean up.

    cJSON_Delete(root);
    cJSON_Delete(info);
    free(mod_introed);
    free(length_str);
}

void get_recent(char* rct,const char* token){

    // Parsing from first json respond.

    cJSON* root=cJSON_Parse(rct);

    // Check if there is no score.

    if(cJSON_GetArraySize(root)==0){
        LOG("This user did not play recently.");
        return;
    }

    cJSON* score=cJSON_GetArrayItem(root,0);
    cJSON* user=cJSON_GetObjectItem(score,"user");
    cJSON* username=cJSON_GetObjectItem(user,"username");
    cJSON* country_code=cJSON_GetObjectItem(user,"country_code");
    cJSON* beatmap=cJSON_GetObjectItem(score,"beatmap");
    cJSON* mode=cJSON_GetObjectItem(beatmap,"mode");
    cJSON* diff=cJSON_GetObjectItem(beatmap,"version");
    cJSON* sr=cJSON_GetObjectItem(beatmap,"difficulty_rating");
    cJSON* length=cJSON_GetObjectItem(beatmap,"hit_length");
    cJSON* bid=cJSON_GetObjectItem(beatmap,"id");
    cJSON* rank=cJSON_GetObjectItem(score,"rank");
    cJSON* mods=cJSON_GetObjectItem(score,"mods");
    cJSON* score_value=cJSON_GetObjectItem(score,"score");
    cJSON* pp=cJSON_GetObjectItem(score,"pp");
    cJSON* combo=cJSON_GetObjectItem(score,"max_combo");
    cJSON* accuracy=cJSON_GetObjectItem(score,"accuracy");
    cJSON* statistics=cJSON_GetObjectItem(score,"statistics");
    cJSON* geki=cJSON_GetObjectItem(statistics,"count_geki");
    cJSON* great=cJSON_GetObjectItem(statistics,"count_300");
    cJSON* katu=cJSON_GetObjectItem(statistics,"count_katu");
    cJSON* ok=cJSON_GetObjectItem(statistics,"count_100");
    cJSON* meh=cJSON_GetObjectItem(statistics,"count_50");
    cJSON* miss=cJSON_GetObjectItem(statistics,"count_miss");
    cJSON* beatmapset=cJSON_GetObjectItem(score,"beatmapset");
    cJSON* artist=cJSON_GetObjectItem(beatmapset,"artist");
    cJSON* title=cJSON_GetObjectItem(beatmapset,"title");

    // Another.

    char* beatmap_info=get_beatmap_info(bid->valueint,token);

    cJSON* info=cJSON_Parse(beatmap_info);
    cJSON* full_combo=cJSON_GetObjectItem(info,"max_combo");

    // Format time pattern.

    char* length_str=strfsec(length->valueint);

    // Mod introduction.

    char* mod_introed=strf_mod_intro(mods);

    // osu!mania specifies.

    int flag=strcmp(mode->valuestring,"mania");

    if(!flag){
        cJSON* cs=cJSON_GetObjectItem(beatmap,"cs");
        printf("%s (%s): %s (%dK)\n",username->valuestring,country_code->valuestring,mode->valuestring,cs->valueint);
    }
    else{
        printf("%s (%s): %s\n",username->valuestring,country_code->valuestring,mode->valuestring);
    }
    printf("%s - %s [%s]\n",artist->valuestring,title->valuestring,diff->valuestring);
    printf("%.2f* %s\n",sr->valuedouble,length_str);
    printf("[%s]%s%d (%.3fpp)\n",rank->valuestring,mod_introed,score_value->valueint,pp->valuedouble);
    printf("%dx / %dx // %.3f%%\n",combo->valueint,full_combo->valueint,100*accuracy->valuedouble);
    
    // osu!mania specifies.

    if(!flag){
        float precision=geki->valuedouble/great->valuedouble;
        printf("%d+%d(%.1f) / %d / %d / %d / %d\n",great->valueint,geki->valueint,precision,katu->valueint,ok->valueint,meh->valueint,miss->valueint);
    }
    else{
        printf("%d / %d / %d / %d\n",great->valueint,ok->valueint,meh->valueint,miss->valueint);
    }

    // Provide beatmap URL.

    printf("https://osu.ppy.sh/b/%d\n",bid->valueint);

    // Clean up.

    cJSON_Delete(root);
    cJSON_Delete(info);
    free(mod_introed);
    free(length_str);
    free(beatmap_info);
}
