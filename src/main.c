//
//  main.c
//  osu-utils
//
//  Created by Merry on 2023/9/9.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "utils/core/auth/OAuth.h"
#include "utils/core/op/Generic.h"
#include "utils/core/op/Bpanalyze.h"

int main(void){

    // Check if Cache folder exists, if not will create one.

    struct stat st={0};
    if(stat("Cache",&st)==-1){
        mkdir("Cache",0755);
    }

/* Not going to 
    // Authorization request.
    char flag;
    printf("%s","Do you want to give permission to this program?(y=OK, n=Cancel)\n");
    r=scanf("%c",&flag);
    if((r==1)&&flag=='y'){
        get_code_request();
        LOG("Successfully get access.");
    }
*/
    curl_global_init(CURL_GLOBAL_ALL);
    char token[1000]={'\0'};

    // Check if token file exists.

    if(test_file_existence("Cache/token.json")){
        LOG("Read existing token.");
        read_token(token,0);
    }
    else{

        // Simply get token.

        LOG("Haven't got a token, will get one.");
        get_token();
    }

    while(1){
        switch(menu_select()){
        case 0:
            LOG("Exiting...");
//            curl_global_cleanup();
            exit(0);
            break;
        case 1:
            get_beatmapsets(token);
            break;
        case 2:
            Bpa(0,token);
            break;
        case 3:
            Bpa(1,token);
            break;
        case 4:
            score(0,token);
            break;
        case 5:
            score(1,token);
            break;
        case 6:
            recent(1,1,1,token);
            break;
        case 7:
            recent(1,0,1,token);
            break;
        case 8:
            recent(1,1,0,token);
            break;
        case 9:
            recent(1,0,0,token);
            break;
        case 10:
            calc_mania_pp();
            break;
        case 99:
            Setid();
            break;
        default:
            LOG("Invaild input.");
            break;
        }
    }
    return 0;
}
