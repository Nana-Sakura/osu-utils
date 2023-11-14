#ifndef CheckScore_h
#define CheckScore_h

#include <stdio.h>

#include "utils/core/op/Query.h"
#include "utils/core/profile/AccountProfile.h"
#include "utils/extra/score/Score.h"
#include "utils/uic/CommandLine.h"

void score(int target,const char* token);
void recent_score(int target,int check_target,int include_fails,const char* cc_token);

#endif /* CheckScore_h */
