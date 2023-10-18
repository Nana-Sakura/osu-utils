#include "utils/core/op/Query.h"

char* get_score_list(struct personal_info info,int offset,int limit,int check_target,int include_fails,const char* cc_token){
    char url[150];
    sprintf(url,"https://osu.ppy.sh/api/v2/users/%d/scores/%s?include_fails=%d&mode=%s&limit=%d&offset=%d",info.uid,check_target_Strings[check_target],include_fails,osu_mode_Strings[info.mode],limit,offset);
    return curl_get_request(url,cc_token);
}

char* get_beatmap_score(struct personal_info info,int beatmap_id,const char* cc_token){
    char url[150];
    sprintf(url,"https://osu.ppy.sh/api/v2/beatmaps/%d/scores/users/%d?mode=%s&mods=minus",beatmap_id,info.uid,osu_mode_Strings[info.mode]);
    return curl_get_request(url,cc_token);
}

char* get_beatmap_info(int beatmap_id,const char* cc_token){
    char url[100];
    sprintf(url,"https://osu.ppy.sh/api/v2/beatmaps/lookup?id=%d",beatmap_id);
    return curl_get_request(url,cc_token);
}

char* get_own_personal_info(const char* acg_token){
    const char* url="https://osu.ppy.sh/api/v2/me";
    return curl_get_request(url,acg_token);
}

char* get_personal_info(const char* username,const char* cc_token){
    char url[100];
    sprintf(url,"https://osu.ppy.sh/api/v2/users/%s",username);
    return curl_get_request(url,cc_token);
}
