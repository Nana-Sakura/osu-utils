#include <curl/curl.h>
#include <sstream>
#include <cstring>
#include <log.hh>

#include "utils/core/network/Requests.hh"

namespace Utils{
    namespace Network{

        Requests::Requests(const std::string& u,const std::string& d,const std::string& cc_token){
            url=u;
            data=d;
            token=cc_token;
            chunk={0};
        }

        std::string Requests::curl_get_request(){
            CURL* eh=curl_easy_init();
            if(eh){
                std::stringstream oauth;
                struct curl_slist* list;
                oauth<<"Authorization: Bearer "<<token;
                list=curl_slist_append(NULL,"Content-Type: application/json");
                list=curl_slist_append(list,"Accept: application/json");
                list=curl_slist_append(list,oauth.str().c_str());
                curl_easy_setopt(eh,CURLOPT_URL,url.c_str());
                curl_easy_setopt(eh,CURLOPT_HTTPHEADER,list);
                curl_easy_setopt(eh,CURLOPT_WRITEFUNCTION,cb);
                curl_easy_setopt(eh,CURLOPT_WRITEDATA,(void*) &chunk);
                curl_easy_setopt(eh,CURLOPT_TIMEOUT,30);
                curl_easy_setopt(eh,CURLOPT_SSL_VERIFYPEER,0);
                curl_easy_perform(eh);
                curl_easy_cleanup(eh);

                return chunk.response;
            }
            else{
                LOG("Null Pointer Exception.");
                exit(16);
            }
        }

        std::string Requests::curl_post_request(){
            CURL* eh=curl_easy_init();
            if(eh){
                struct curl_slist* list;
                list=curl_slist_append(NULL,"Content-Type: application/x-www-form-urlencoded");
                list=curl_slist_append(list,"Accept: application/json");
                curl_easy_setopt(eh,CURLOPT_URL,"https://osu.ppy.sh/oauth/token");
                curl_easy_setopt(eh,CURLOPT_HTTPHEADER,list);
                curl_easy_setopt(eh,CURLOPT_POSTFIELDSIZE,data.length());
                curl_easy_setopt(eh,CURLOPT_POSTFIELDS,data.c_str());
                curl_easy_setopt(eh,CURLOPT_WRITEFUNCTION,cb);
                curl_easy_setopt(eh,CURLOPT_WRITEDATA,(void*) &chunk);
                curl_easy_setopt(eh,CURLOPT_TIMEOUT,30);
                curl_easy_setopt(eh,CURLOPT_SSL_VERIFYPEER,0);
                curl_easy_perform(eh);
                curl_easy_cleanup(eh);

                return chunk.response;
            }
            else{
                LOG("Null Pointer Exception.");
                exit(16);
            }
        }

        std::string Requests::curl_get_object_request(){
            CURL* eh=curl_easy_init();
            if(eh){
                curl_easy_setopt(eh,CURLOPT_URL,url.c_str());
                curl_easy_setopt(eh,CURLOPT_FOLLOWLOCATION,1);
                curl_easy_setopt(eh,CURLOPT_WRITEFUNCTION,cb);
                curl_easy_setopt(eh,CURLOPT_WRITEDATA,(void*) &chunk);
                curl_easy_setopt(eh,CURLOPT_TIMEOUT,30);
                curl_easy_setopt(eh,CURLOPT_SSL_VERIFYPEER,0);
                curl_easy_perform(eh);
                curl_easy_cleanup(eh);

                return chunk.response;
            }
            else{
                LOG("Null Pointer Exception.");
                exit(16);
            }
        }

        Requests::~Requests(){
            free(chunk.response);
        }

        ssize_t cb(char* buffer,size_t size,size_t nitems,void* userdata){
            size_t realsize=size*nitems;
            struct memory* mem=(struct memory*) userdata;
            char* ptr=(char*) realloc(mem->response,mem->size+realsize+1);
            if(buffer==NULL){
                LOG("Out Of Memory Exception.");
                exit(16);
            }
            mem->response=ptr;
            std::memcpy(&(mem->response[mem->size]),buffer,realsize);
            mem->size+=realsize;
            mem->response[mem->size]=0;
            return realsize;
        }

    }
}
