#ifndef Protocol_h
#define Protocol_h

#include <stdbool.h>
#include <webview.h>
#include <cJSON.h>
#include <log.h>

void init_main_window(void* window);
void webview_main_window_cb(const char* seq,const char* req,void* arg);


#endif
