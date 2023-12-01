#include <iostream>
#include <iomanip>

#include "utils/core/score/Analyze.hh"

namespace Utils{
    namespace Score{

        void score_analyze(struct Utils::Commons::personal_info info,const std::string& score_list){

            struct Utils::Commons::ranking_analyze statistics={0};

            cJSON* mod_intro_statistics=cJSON_CreateObject();
            cJSON* root=cJSON_Parse(score_list.c_str());
            int arraysize=cJSON_GetArraySize(root);

            for(int i=0;i<arraysize;i++){

                cJSON* score_info=cJSON_GetArrayItem(root,i);

                // Get username.

                if(!i){
                    cJSON* user=cJSON_GetObjectItem(score_info,"user");
                    cJSON* username=cJSON_GetObjectItem(user,"username");
                    std::cout<<username->valuestring<<" ["<<osu_mode_Strings[info.mode]<<"]"<<std::endl;
                }

                // Parsing.

                cJSON* pp=cJSON_GetObjectItem(score_info,"pp");
                cJSON* rank=cJSON_GetObjectItem(score_info,"rank");
                cJSON* perfect_flag=cJSON_GetObjectItem(score_info,"perfect");
                cJSON* mods=cJSON_GetObjectItem(score_info,"mods");

                bool flag=perfect_flag->valueint;
                std::string ranking=rank->valuestring;
                int mod_sum=cJSON_GetArraySize(mods);

                // Get Mod intro count.

                for(int k=0;k<mod_sum;k++){
                    cJSON* mod=cJSON_GetArrayItem(mods,k);
                    if(cJSON_HasObjectItem(mod_intro_statistics,mod->valuestring)==0){
                        cJSON_AddNumberToObject(mod_intro_statistics,mod->valuestring,1);
                    }
                    else{
                        cJSON* num=cJSON_GetObjectItem(mod_intro_statistics,mod->valuestring);
                        int number=num->valueint;
                        number++;
                        cJSON_SetNumberValue(num,number);
                    }
                }

                // Get ppmax and ppmin.

                if(!i){
                    statistics.ppmax=pp->valuedouble;
                }
                if(i==arraysize-1){
                    statistics.ppmin=pp->valuedouble;
                }

                // Print first 5 and last 5 while accumulating related data.

                if((i<5)||(i>=arraysize-5)){
                    cJSON* acc=cJSON_GetObjectItem(score_info,"accuracy");
                    
                    // Get Mods applied.
                    
                    std::string mods_string=Utils::Commons::strf_mod_intro(mods);
                    std::cout<<"#"<<std::setw(3)<<(i+1)<<" "<<std::setw(7)<<std::fixed<<std::setprecision(2)<<(pp->valuedouble)<<" "<<std::setw(6)<<std::fixed<<std::setprecision(2)<<(100.0*acc->valuedouble)<<"% "<<std::setw(2)<<ranking<<mods_string<<std::endl;
                }

                // Accumulate.

                statistics.avgpp+=pp->valuedouble;

                if(flag){
                    statistics.fc++;
                }
                if(ranking.compare("S")==0){
                    statistics.s++;
                }
                if(ranking.compare("SH")==0){
                    statistics.sh++;
                }
                if(ranking.compare("X")==0){
                    statistics.x++;
                }
                if(ranking.compare("XH")==0){
                    statistics.xh++;
                }
            }
            
            statistics.avgpp/=(float)arraysize;

            // Mod Intro.

            std::cout<<"Mod Introduction: "<<std::endl;
            cJSON* now=mod_intro_statistics->child;
            while(now!=NULL){
                std::string key=now->string;
                int value=now->valueint;
                std::cout<<key<<": "<<value<<"; ";
                now=now->next;
            }
            
            std::cout<<std::endl;
            
            // Misc informations.

            std::cout<<"There are "<<(statistics.s+statistics.sh+statistics.x+statistics.xh)<<" S ranks or above in your bplist."<<std::endl;
            std::cout<<"There are "<<statistics.fc<<" FC in your bplist."<<std::endl;
            std::cout<<"There are "<<(statistics.x+statistics.xh)<<" SS ranks in your bplist."<<std::endl;
            std::cout<<"The range of your bplist is "<<std::fixed<<std::setprecision(2)<<(statistics.ppmax-statistics.ppmin)<<"."<<std::endl;
            std::cout<<"The average pp of the scores on your bplist is "<<std::fixed<<std::setprecision(2)<<statistics.avgpp<<"."<<std::endl;

            // Cleanup.

            cJSON_Delete(root);
            cJSON_Delete(mod_intro_statistics);
        }

    
    }
}
