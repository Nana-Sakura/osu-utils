#include "utils/core/op/CalcManiaPP.h"

void calc_mania_pp(void){
    struct statistics_mania i;
    int ez,nf;

    printf("Type in the count of rainbow 300: ");
    while((scanf("%u",&i.perfect)<1)||(i.perfect<0)){
        LOG("Count format error, please type in again.");
        fflush(stdin);
    }

    printf("Type in the count of yellow 300: ");
    while((scanf("%u",&i.great)<1)||(i.great<0)){
        LOG("Count format error, please type in again.");
        fflush(stdin);
    }

    printf("Type in the count of 200: ");
    while((scanf("%u",&i.good)<1)||(i.good<0)){
        LOG("Count format error, please type in again.");
        fflush(stdin);
    }

    printf("Type in the count of 100: ");
    while((scanf("%u",&i.ok)<1)||(i.ok<0)){
        LOG("Count format error, please type in again.");
        fflush(stdin);
    }

    printf("Type in the count of 50: ");
    while((scanf("%u",&i.meh)<1)||(i.meh<0)){
        LOG("Count format error, please type in again.");
        fflush(stdin);
    }

    printf("Type in the count of miss: ");
    while((scanf("%u",&i.miss)<1)||(i.miss<0)){
        LOG("Count format error, please type in again.");
        fflush(stdin);
    }

    printf("Type in the Star Rating of the beatmap: ");
    while((scanf("%f",&i.sr)<1)||(i.sr<0)){
        LOG("Star Rating format error, please type in again.");
        fflush(stdin);
    }

    printf("Type in the if you have applied EZ mod(0 stands for no, 1 for yes): ");
    while((scanf("%d",&ez)<1)||(ez<0)||(ez>1)){
        LOG("Input format error, please type in again.");
        fflush(stdin);
    }

    printf("Type in the if you have applied NF mod(0 stands for no, 1 for yes): ");
    while((scanf("%d",&nf)<1)||(nf<0)||(nf>1)){
        LOG("Input format error, please type in again.");
        fflush(stdin);
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
