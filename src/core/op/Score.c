//
//  Getscore.c
//  osu-utils
//
//  Created by Merry on 2023/9/20.
//

#include "utils/core/op/Score.h"

char* get_score_list(int uid,int mode_id,int offset,int limit,int check_mode_id,int include_fails,const char* token){
    char* mode=select_mode(mode_id);
    char* check_mode=select_check_mode(check_mode_id);
    char url[114];
    sprintf(url,"https://osu.ppy.sh/api/v2/users/%d/scores/%s?include_fails=%d&mode=%s&limit=%d&offset=%d",uid,check_mode,include_fails,mode,limit,offset);
    return curl_request(url,token);
}

char* get_beatmap_score(int uid,int mode_id,int beatmap_id,const char* token){
    char url[114];
    char* mode=select_mode(mode_id);
    sprintf(url,"https://osu.ppy.sh/api/v2/beatmaps/%d/scores/users/%d?mode=%s&mods=minus",beatmap_id,uid,mode);
    return curl_request(url,token);
}

char* get_beatmap_info(int beatmap_id, const char* token){
    char url[100];
    sprintf(url,"https://osu.ppy.sh/api/v2/beatmaps/lookup?id=%d",beatmap_id);
    return curl_request(url,token);
}

void get_score(char* beatmapscore, char* beatmapinfo){

    // Parsing from first json respond.

    cJSON* root=cJSON_Parse(beatmapscore);
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

    cJSON* info=cJSON_Parse(beatmapinfo);
    cJSON* beatmapset=cJSON_GetObjectItem(info,"beatmapset");
    cJSON* artist=cJSON_GetObjectItem(beatmapset,"artist");
    cJSON* title=cJSON_GetObjectItem(beatmapset,"title");
    cJSON* full_combo=cJSON_GetObjectItem(info,"max_combo");

    // Format time pattern.

    char* length_str=strfsec(length->valueint);

    // Mod introduction.

    char* mod_introed=mod_intro(mods);

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
    printf("[%s] %s%d (%.3fpp)\n",rank->valuestring,mod_introed,score_value->valueint,pp->valuedouble);
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

    char* mod_introed=mod_intro(mods);

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
    printf("[%s] %s%d (%.3fpp)\n",rank->valuestring,mod_introed,score_value->valueint,pp->valuedouble);
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
