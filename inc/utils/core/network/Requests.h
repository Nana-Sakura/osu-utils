#ifndef Requests_h
#define Requests_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <log.h>

struct memory{
    char* response;
    size_t size;
};

size_t cb(char* buffer,size_t size,size_t nitems,void* userdata);
char* curl_get_request(const char* path_to_source,const char* token);
char* curl_post_request(const char* data_to_post);
char* curl_get_object_request(const char* path_to_source);

#endif /* Requests_h */