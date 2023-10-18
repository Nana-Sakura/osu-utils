#ifndef AccountProfile_h
#define AccountProfile_h

#include <stdio.h>
#include "cJSON.h"

#include "utils/core/auth/OAuth.h"
#include "utils/core/op/Query.h"
#include "utils/core/util/Generic.h"

struct personal_info manual_get_info(void);
struct personal_info auto_get_self_info(void);
struct personal_info semi_auto_get_info(const char* cc_token);
struct personal_info read_info(void);
void set_id(struct personal_info info);
void manual_set_id(void);
void auto_set_id(void);

#endif /* AccountProfile_h */
