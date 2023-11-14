#ifndef AccountProfile_h
#define AccountProfile_h

#include <stdio.h>
#include <cJSON.h>

#include "utils/core/auth/OAuth.h"
#include "utils/core/op/Query.h"
#include "utils/uic/CommandLine.h"
#include "utils/util/Generic.h"

struct personal_info auto_get_self_info(struct personal_info on_error(const char* cc_token),const char* cc_token);
struct personal_info semi_auto_get_info(const char* cc_token);
struct personal_info read_info(const char* cc_token);
struct personal_info on_error(const char* cc_token);
void set_id(struct personal_info info);
void manual_set_id(void);
void auto_set_id(const char* cc_token);

#endif /* AccountProfile_h */
