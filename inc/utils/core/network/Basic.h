//
//  Basic.h
//  osu-utils
//
//  Created by Merry on 2023/9/20.
//

#ifndef Basic_h
#define Basic_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"

struct memory{
    char* response;
    size_t size;
};

size_t cb(char* buffer,size_t size,size_t nitems,void* userdata);

#endif /* Basic_h */
