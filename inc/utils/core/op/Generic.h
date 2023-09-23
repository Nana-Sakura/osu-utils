//
//  Generic.h
//  osu-utils
//
//  Created by Merry on 2023/9/20.
//

#ifndef Generic_h
#define Generic_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "log.h"

char* select_mode(int mode_id);
bool test_file_existence(char* path);
char* read_file(const char* path);

#endif /* Generic_h */
