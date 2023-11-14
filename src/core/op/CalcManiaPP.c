#include "utils/core/op/CalcManiaPP.h"

void calc_mania_pp(void){
    
    struct statistics_mania i=get_result_info();

    cJSON* mods=get_essential_mods();

    mania_pp(i,mods);
    
    cJSON_Delete(mods);
}
