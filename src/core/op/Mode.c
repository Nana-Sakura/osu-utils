//
//  Mode.c
//  osu-utils
//
//  Created by Merry on 2023/9/20.
//

#include "Mode.h"

char* select_mode(uint8_t mode_id){
    char* mode;
    switch(mode_id){
        case 0:
            mode="osu";
            break;
        case 1:
            mode="taiko";
            break;
        case 2:
            mode="fruits";
            break;
        case 3:
            mode="mania";
            break;
        default:
            fprintf(stderr,"Mode error.\n");
            exit(-4);
            break;
    }
    return mode;
}
