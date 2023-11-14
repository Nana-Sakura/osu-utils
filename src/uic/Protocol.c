#include "utils/uic/Protocol.h"

static webview_t main_window;
static bool main_window_ready=false;

void init_main_window(void* window){
    if(window==NULL){
        main_window_ready=false;
        return;
    }
    main_window=(webview_t)window;
    webview_bind(main_window,"SYS",webview_main_window_cb,NULL);
}

void webview_main_window_cb(const char* seq,const char* req,void* arg){
    cJSON* args=cJSON_Parse(req);
    if(cJSON_IsArray(args)){
        cJSON* chn=cJSON_GetArrayItem(args,0);
        cJSON* pid=cJSON_GetArrayItem(args,1);
        cJSON* par=cJSON_GetArrayItem(args,2);
        int pid_int=(int)cJSON_GetNumberValue(pid);
        if(cJSON_IsString(chn)){
            char* chn_str=chn->valuestring;
            if(strcmp(chn_str,"Ready")==0){
                main_window_ready=true;
            }
        }
        
    }
}
