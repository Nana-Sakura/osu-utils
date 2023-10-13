//
//  Calcpp.c
//  osu-utils
//
//  Created by Merry on 2023/10/4.
//

#include "utils/core/op/Calcpp.h"

// osu!mania specifies.

float difficulty(float accpp){
    float ans;
    if(accpp<=0.8){
        ans=0;
    }
    else ans=(accpp-0.8)/0.2;
    return ans;
}

int perfect_value(int score_mode){
    int result;
    switch(score_mode){
    case 0:
        result=300; // Acc V1.
        break;
    case 1:
        result=305; // Acc V2.
        break;
    case 2:
        result=315; // Acc Lazer.
        break;
    case 3:
        result=320; // Accpp.
        break;
    default:
        LOG("Coding error here.\n");
        exit(16);
    }
    return result;
}

float acc_calc(int score_mode,struct statistics_mania i){
    int pf=perfect_value(score_mode);
    return (float)(pf*i.perfect+300*i.great+200*i.good+100*i.ok+50*i.meh)/(float)(pf*(i.perfect+i.great+i.good+i.ok+i.meh+i.miss));
}

float multiplier(cJSON* mods){
    bool ez=0;
    bool nf=0;
    int size=cJSON_GetArraySize(mods);
    for(int i=0;i<size;i++){
        if(strcmp(cJSON_GetArrayItem(mods,i)->valuestring,"EZ")==0){
            ez=1;
        }
        if(strcmp(cJSON_GetArrayItem(mods,i)->valuestring,"NF")==0){
            nf=1;
        }
    }
    float ans=8.0;
    if(ez){
        ans*=0.5;
    }
    if(nf){
        ans*=0.75;
    }
    return ans;
}

float maximumpp(struct statistics_mania i,float multiplier){
    float star_rating=i.sr;
    uint32_t notes=i.perfect+i.great+i.good+i.ok+i.meh+i.miss;
    return pow(((star_rating>0.20)?(star_rating-0.15):0.05),2.2)*(1.0+0.1*((notes>1500)?1.0:((float)notes/(float)1500)))*multiplier;
}

void mania_pp(struct statistics_mania i,cJSON* mods){
    float accpp_value=acc_calc(3,i);
    float diff=difficulty(accpp_value);
    float multiplier_value=multiplier(mods);
    float max_pp=maximumpp(i,multiplier_value);

    printf("AccPP: %.3f%%\n",accpp_value*100);
    printf("Difficulty: %.3f%%\n",diff*100);
    printf("if SS: %.3f pp\n",max_pp);
    printf("Achieved PP: %.3f pp\n",max_pp*diff);
}

// osu! specifies.
/* Not Completed.

float guess_effective_miss_count(struct statistics_osu data,struct beatmap map){
    float effective_miss_count;
    float combo_based_miss_count=0;

    // TODO: Haven't got the calculate method, guess.

    float beatmap_max_combo=map.max_combo;
    
    if(map.sliders>0){
        float FC_Threshold=beatmap_max_combo-0.1*map.sliders;
        if(data.combo<FC_Threshold){
            combo_based_miss_count=FC_Threshold/fmaxf(1,beatmap_max_combo);
        }
    }
    combo_based_miss_count=fminf(combo_based_miss_count,(float)(data.ok+data.meh+data.miss));
    effective_miss_count=fmaxf((float)data.miss,combo_based_miss_count);
    return effective_miss_count;
}

float calc_aim(struct statistics_osu data,struct beatmap map){
    float aim_value=pow((float)5*fmaxf((float)1,))
}

*/