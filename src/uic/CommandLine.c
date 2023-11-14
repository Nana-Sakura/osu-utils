#include "utils/uic/CommandLine.h"

#define get_input(condition1,condition2,hint_content,log_content)           \
        printf(hint_content);                                               \
        while(condition1){                                                  \
            if(condition2){                                                 \
                exit(0);                                                    \
            }                                                               \
            LOG(log_content);                                               \
            fflush(stdin);                                                  \
        }

int menu_select(void){
    int select;
    printf("\n");
    printf("Type in number to select a function.\n");
    printf("1. Get Mapsets from Best Plays of anyone.\n");
    printf("2. Get Bpht of yourself.\n");
    printf("3. Get Score of a specified beatmap of yourself.\n");
    printf("4. Get Score of your recently passed beatmap.\n");
    printf("5. Get Score of your recently played beatmap.\n");
    printf("6. Get Bpht of anyone.\n");
    printf("7. Get Score of a specified beatmap of anyone.\n");
    printf("8. Get Score of other's recently passed beatmap.\n");
    printf("9. Get Score of other's recently played beatmap.\n");
    printf("10.Calculate pp of any beatmap.(Currently mania only)\n");
    printf("99.Set your ID and default game mode.\n");
    printf("0. Quit.\n");
    
    get_input(
        ((scanf("%d",&select)<1)||(select<0)||(select>99)),
        (scanf("%d",&select)==-1),
        "Your selection: ",
        "Selection error, please type in again."
    );

    printf("\n");
    return select;
}

struct statistics_mania get_result_info(void){

    struct statistics_mania i;

    get_input(
        ((scanf("%u",&i.perfect)<1)||(i.perfect<0)),
        scanf("%u",&i.perfect)==-1,
        "Type in the count of rainbow 300: ",
        "Count format error, please type in again."
    );

    get_input(
        ((scanf("%u",&i.great)<1)||(i.great<0)),
        scanf("%u",&i.great)==-1,
        "Type in the count of yellow 300: ",
        "Count format error, please type in again."
    );

    get_input(
        ((scanf("%u",&i.good)<1)||(i.good<0)),
        scanf("%u",&i.good)==-1,
        "Type in the count of 200: ",
        "Count format error, please type in again."
    );

    get_input(
        ((scanf("%u",&i.ok)<1)||(i.ok<0)),
        scanf("%u",&i.ok)==-1,
        "Type in the count of 100: ",
        "Count format error, please type in again."
    );

    get_input(
        ((scanf("%u",&i.meh)<1)||(i.meh<0)),
        scanf("%u",&i.meh)==-1,
        "Type in the count of 50: ",
        "Count format error, please type in again."
    );

    get_input(
        ((scanf("%u",&i.miss)<1)||(i.miss<0)),
        scanf("%u",&i.miss)==-1,
        "Type in the count of miss: ",
        "Count format error, please type in again."
    );

    get_input(
        ((scanf("%f",&i.sr)<1)||(i.sr<0)),
        scanf("%f",&i.sr)==-1,
        "Type in the Star Rating of the beatmap: ",
        "Star Rating format error, please type in again."
    );            

    return i;
}

cJSON* get_essential_mods(void){

    int ez,nf;

    get_input(
        ((scanf("%d",&ez)<1)||(ez<0)||(ez>1)),
        (scanf("%d",&ez)==-1),
        "Type in the if you have applied EZ mod(0 stands for no, 1 for yes): ",
        "Input format error, please type in again."
    );

    get_input(
        ((scanf("%d",&nf)<1)||(nf<0)||(nf>1)),
        (scanf("%d",&nf)==-1),
        "Type in the if you have applied NF mod(0 stands for no, 1 for yes): ",
        "Input format error, please type in again."
    );

    cJSON* mods=cJSON_CreateArray();
    if(ez){
        cJSON* ez_obj=cJSON_CreateString("EZ");
        cJSON_AddItemToArray(mods,ez_obj);
    }
    if(nf){
        cJSON* nf_obj=cJSON_CreateString("NF");
        cJSON_AddItemToArray(mods,nf_obj);
    }

    return mods;
}

struct personal_info manual_get_info(void){

    struct personal_info info;
    
    get_input(
        ((scanf("%d",&info.uid)<1)||(info.uid<0)),
        (scanf("%d",&info.uid)==-1),
        "Type in the uid: ",
        "uid format error, please type in again."
    );

    get_input(
        ((scanf("%d",&info.mode)<1)||(info.mode>3)||(info.mode<0)),
        (scanf("%d",&info.mode)==-1),
        "Type in the mode(0 stands for std, 1 for taiko, 2 for ctb, 3 for mania): ",
        "Mode format error, please type in again."
    );

    return info;
}

int get_beatmap_id(void){

    int beatmap_id;

    get_input(
        (scanf("%d",&beatmap_id)<1),
        (scanf("%d",&beatmap_id)==-1),
        "Type in beatmap id: ",
        "beatmap id format error, please type in again."
    );

    return beatmap_id;
}

struct BeatmapSet_Range get_beatmapset_range(void){
    
    struct BeatmapSet_Range range={0};
    int r;

    get_input(
        ((scanf("%d",&r)<1)||(r<0)||(r>1)),
        (scanf("%d",&r)==-1),
        "Type in if you want to download all of the beatmaps on the list(0 for Yes, 1 for No): ",
        "Option format error, please type in again."
    );

    if(r){
        
        get_input(
            ((scanf("%d",&range.offset)<1)||(range.offset>100)),
            (scanf("%d",&range.offset)==-1),
            "Type in the start position of the bplist you want to get(0 for default): ",
            "Offset format error, please type in again."
        );

        get_input(
            ((scanf("%d",&range.limit)<1)||(range.limit>100)),
            (scanf("%d",&range.limit)==-1),
            "Type in the end position of the bplist you want to get(100 for default): ",
            "Limit format error, please type in again."
        );

    }
    else{
        range.offset=0;
        range.limit=100;
    }

    return range;
}
