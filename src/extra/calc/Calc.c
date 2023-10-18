#include "utils/extra/calc/Calc.h"

// osu!mania specifies.

float difficulty(float accpp){
    float ans;
    if(accpp<=0.8){
        ans=0;
    }
    else ans=(accpp-0.8)/0.2;
    return ans;
}

float acc_calc(int pft,struct statistics_mania i){
    return (float)(perfect_value[pft]*i.perfect+300*i.great+200*i.good+100*i.ok+50*i.meh)/(float)(perfect_value[pft]*(i.perfect+i.great+i.good+i.ok+i.meh+i.miss));
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

// TODO: osu!, osu!taiko, osu!catch specifies.
