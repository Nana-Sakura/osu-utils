#include "utils/core/profile/AccountProfile.h"

struct personal_info auto_get_self_info(struct personal_info on_error(const char* cc_token),const char* cc_token){
    struct personal_info info={0};

    char* acg_token=read_token(0);
    char* info_json=get_own_personal_info(acg_token);
    cJSON* root=cJSON_Parse(info_json);
    cJSON* uid=cJSON_GetObjectItem(root,"id");
    cJSON* mode=cJSON_GetObjectItem(root,"playmode");

    if(uid==NULL){
        cJSON_Delete(root);
        free(info_json);
        free(acg_token);
        return on_error(cc_token);
    }

    info.uid=uid->valueint;
    info.mode=search_array(osu_mode_Strings,4,mode->valuestring);
    
    cJSON_Delete(root);
    free(info_json);
    free(acg_token);

    return info;
}

struct personal_info semi_auto_get_info(const char* cc_token){

    struct personal_info info={0};
    char* username=NULL;

    // Username is no longer than 15 characters.

    printf("Type in the username(max 15 chars): ");

    int i=0;
    char c;
    while((i>15)||(i==0)){
        i=0;
        c=fgetc(stdin);
        while((c!=EOF)&&(c!='\n')){
            char* ptr=(char*) realloc(username,i+2);
            username=ptr;
            username[i]=(c==' ')?'_':c;
            i++;
            c=fgetc(stdin);
        }
        if(i>15){
            LOG("Username format error(no more than 15 chars), please type in again.");
            fflush(stdin);
        }
    }

    char* info_json=get_personal_info(username,cc_token);
    cJSON* root=cJSON_Parse(info_json);
    cJSON* uid=cJSON_GetObjectItem(root,"id");
    cJSON* mode=cJSON_GetObjectItem(root,"playmode");

    info.uid=uid->valueint;
    info.mode=search_array(osu_mode_Strings,4,mode->valuestring);

    cJSON_Delete(root);
    free(info_json);
    return info;
}

struct personal_info read_info(const char* cc_token){
    struct personal_info result={0};

    while(get_file_size("Cache/user.json")==-1){
        LOG("You haven't set your ID and default mode, setup now.");
        auto_set_id(cc_token);
    }

    char* info_json=read_file("Cache/user.json");
    cJSON* root=cJSON_Parse(info_json);
    
    cJSON* uid_object=cJSON_GetObjectItem(root,"uid");
    cJSON* mode_object=cJSON_GetObjectItem(root,"mode");
    result.uid=uid_object->valueint;
    result.mode=mode_object->valueint;

    cJSON_Delete(root);
    free(info_json);
    return result;
}

struct personal_info on_error(const char* cc_token){
    LOG("Facing Network Error. Retrying...");
    return auto_get_self_info(semi_auto_get_info,cc_token);
}

void set_id(struct personal_info info){

    cJSON* info_json=cJSON_CreateObject();
    cJSON_AddNumberToObject(info_json,"uid",info.uid);
    cJSON_AddNumberToObject(info_json,"mode",info.mode);
    char* json=cJSON_Print(info_json);

    write_file("Cache/user.json",json,"w+");

    cJSON_Delete(info_json);
}

void manual_set_id(void){

    struct personal_info info=manual_get_info();
    
    set_id(info);
}

void auto_set_id(const char* cc_token){

    struct personal_info info=auto_get_self_info(on_error,cc_token);

    set_id(info);
}
