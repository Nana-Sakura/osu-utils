#include <iostream>
#include <iomanip>
#include <cJSON.h>
#include <log.hh>
#include "utils/core/score/ParseScore.hh"
#include "utils/core/op/Query.hh"
#include "utils/util/Commons.hh"

namespace Utils{
    namespace Score{

        void parse_specified_score(const std::string& beatmap_score,const std::string& beatmap_info){

            // Parsing from first json respond.

            cJSON* root=cJSON_Parse(beatmap_score.c_str());
            cJSON* score=cJSON_GetObjectItem(root,"score");
            cJSON* user=cJSON_GetObjectItem(score,"user");
            cJSON* username=cJSON_GetObjectItem(user,"username");
            cJSON* country_code=cJSON_GetObjectItem(user,"country_code");
            cJSON* beatmap=cJSON_GetObjectItem(score,"beatmap");
            cJSON* mode=cJSON_GetObjectItem(beatmap,"mode");
            cJSON* diff=cJSON_GetObjectItem(beatmap,"version");
            cJSON* sr=cJSON_GetObjectItem(beatmap,"difficulty_rating");
            cJSON* length=cJSON_GetObjectItem(beatmap,"hit_length");
            cJSON* bid=cJSON_GetObjectItem(beatmap,"id");
            cJSON* rank=cJSON_GetObjectItem(score,"rank");
            cJSON* mods=cJSON_GetObjectItem(score,"mods");
            cJSON* score_value=cJSON_GetObjectItem(score,"score");
            cJSON* pp=cJSON_GetObjectItem(score,"pp");
            cJSON* combo=cJSON_GetObjectItem(score,"max_combo");
            cJSON* accuracy=cJSON_GetObjectItem(score,"accuracy");
            cJSON* statistics=cJSON_GetObjectItem(score,"statistics");
            cJSON* geki=cJSON_GetObjectItem(statistics,"count_geki");
            cJSON* great=cJSON_GetObjectItem(statistics,"count_300");
            cJSON* katu=cJSON_GetObjectItem(statistics,"count_katu");
            cJSON* ok=cJSON_GetObjectItem(statistics,"count_100");
            cJSON* meh=cJSON_GetObjectItem(statistics,"count_50");
            cJSON* miss=cJSON_GetObjectItem(statistics,"count_miss");
            
            // Another.

            cJSON* info=cJSON_Parse(beatmap_info.c_str());
            cJSON* beatmapset=cJSON_GetObjectItem(info,"beatmapset");
            cJSON* artist=cJSON_GetObjectItem(beatmapset,"artist");
            cJSON* title=cJSON_GetObjectItem(beatmapset,"title");
            cJSON* full_combo=cJSON_GetObjectItem(info,"max_combo");

            // Format time pattern.

            std::string length_str=Utils::Commons::strfsec(length->valueint);

            // Mod introduction.

            std::string mod_introed=Utils::Commons::strf_mod_intro(mods);

            // osu!mania specifies.

            std::string mode_str=mode->valuestring;
            int flag=mode_str.compare("mania");

            if(!flag){
                cJSON* cs=cJSON_GetObjectItem(beatmap,"cs");
                std::cout<<username->valuestring<<" ("<<country_code->valuestring<<"): "<<mode->valuestring<<" ("<<cs->valueint<<"K)"<<std::endl;
            }
            else{
                std::cout<<username->valuestring<<" ("<<country_code->valuestring<<"): "<<mode->valuestring<<std::endl;    
            }
            std::cout<<artist->valuestring<<" - "<<title->valuestring<<" ["<<diff->valuestring<<"]"<<std::endl;
            std::cout<<std::fixed<<std::setprecision(2)<<sr->valuedouble<<"* "<<length_str<<std::endl;
            std::cout<<"["<<rank->valuestring<<"]"<<mod_introed<<score_value->valueint<<" ("<<std::fixed<<std::setprecision(3)<<pp->valuedouble<<"pp)"<<std::endl;
            std::cout<<combo->valueint<<"x / "<<full_combo->valueint<<"x // "<<std::fixed<<std::setprecision(3)<<100*accuracy->valuedouble<<"%"<<std::endl;
            
            // osu!mania specifies.

            if(!flag){
                float precision=geki->valuedouble/great->valuedouble;
                std::cout<<great->valueint<<"+"<<geki->valueint<<"("<<std::fixed<<std::setprecision(1)<<precision<<") / "<<katu->valueint<<" / "<<ok->valueint<<" / "<<meh->valueint<<" / "<<miss->valueint<<std::endl;
            }
            else{
                std::cout<<great->valueint<<" / "<<ok->valueint<<" / "<<meh->valueint<<" / "<<miss->valueint<<std::endl;
            }

            // Provide beatmap URL.

            std::cout<<"https://osu.ppy.sh/b/"<<bid->valueint<<std::endl;

            // Clean up.

            cJSON_Delete(root);
            cJSON_Delete(info);

        }

        void parse_recent_score(const std::string& recent_score,const std::string& cc_token){
            // Parsing from first json respond.

            cJSON* root=cJSON_Parse(recent_score.c_str());

            // Check if there is no score.

            if(cJSON_GetArraySize(root)==0){
                LOG("This user did not play recently.");
                return;
            }

            cJSON* score=cJSON_GetArrayItem(root,0);
            cJSON* user=cJSON_GetObjectItem(score,"user");
            cJSON* username=cJSON_GetObjectItem(user,"username");
            cJSON* country_code=cJSON_GetObjectItem(user,"country_code");
            cJSON* beatmap=cJSON_GetObjectItem(score,"beatmap");
            cJSON* mode=cJSON_GetObjectItem(beatmap,"mode");
            cJSON* diff=cJSON_GetObjectItem(beatmap,"version");
            cJSON* sr=cJSON_GetObjectItem(beatmap,"difficulty_rating");
            cJSON* length=cJSON_GetObjectItem(beatmap,"hit_length");
            cJSON* bid=cJSON_GetObjectItem(beatmap,"id");
            cJSON* rank=cJSON_GetObjectItem(score,"rank");
            cJSON* mods=cJSON_GetObjectItem(score,"mods");
            cJSON* score_value=cJSON_GetObjectItem(score,"score");
            cJSON* pp=cJSON_GetObjectItem(score,"pp");
            cJSON* combo=cJSON_GetObjectItem(score,"max_combo");
            cJSON* accuracy=cJSON_GetObjectItem(score,"accuracy");
            cJSON* statistics=cJSON_GetObjectItem(score,"statistics");
            cJSON* geki=cJSON_GetObjectItem(statistics,"count_geki");
            cJSON* great=cJSON_GetObjectItem(statistics,"count_300");
            cJSON* katu=cJSON_GetObjectItem(statistics,"count_katu");
            cJSON* ok=cJSON_GetObjectItem(statistics,"count_100");
            cJSON* meh=cJSON_GetObjectItem(statistics,"count_50");
            cJSON* miss=cJSON_GetObjectItem(statistics,"count_miss");
            cJSON* beatmapset=cJSON_GetObjectItem(score,"beatmapset");
            cJSON* artist=cJSON_GetObjectItem(beatmapset,"artist");
            cJSON* title=cJSON_GetObjectItem(beatmapset,"title");

            // Another.

            std::string beatmap_info=Utils::Op::get_beatmap_info(bid->valueint,cc_token);

            cJSON* info=cJSON_Parse(beatmap_info.c_str());
            cJSON* full_combo=cJSON_GetObjectItem(info,"max_combo");

            // Format time pattern.

            std::string length_str=Utils::Commons::strfsec(length->valueint);

            // Mod introduction.

            std::string mod_introed=Utils::Commons::strf_mod_intro(mods);

            // osu!mania specifies.

            std::string mode_str=mode->valuestring;
            int flag=mode_str.compare("mania");

            if(!flag){
                cJSON* cs=cJSON_GetObjectItem(beatmap,"cs");
                std::cout<<username->valuestring<<" ("<<country_code->valuestring<<"): "<<mode->valuestring<<" ("<<cs->valueint<<"K)"<<std::endl;
            }
            else{
                std::cout<<username->valuestring<<" ("<<country_code->valuestring<<"): "<<mode->valuestring<<std::endl;    
            }
            std::cout<<artist->valuestring<<" - "<<title->valuestring<<" ["<<diff->valuestring<<"]"<<std::endl;
            std::cout<<std::fixed<<std::setprecision(2)<<sr->valuedouble<<"* "<<length_str<<std::endl;
            std::cout<<"["<<rank->valuestring<<"]"<<mod_introed<<score_value->valueint<<" ("<<std::fixed<<std::setprecision(3)<<pp->valuedouble<<"pp)"<<std::endl;
            std::cout<<combo->valueint<<"x / "<<full_combo->valueint<<"x // "<<std::fixed<<std::setprecision(3)<<100*accuracy->valuedouble<<"%"<<std::endl;
            
            // osu!mania specifies.

            if(!flag){
                float precision=geki->valuedouble/great->valuedouble;
                std::cout<<great->valueint<<"+"<<geki->valueint<<"("<<std::fixed<<std::setprecision(1)<<precision<<") / "<<katu->valueint<<" / "<<ok->valueint<<" / "<<meh->valueint<<" / "<<miss->valueint<<std::endl;
            }
            else{
                std::cout<<great->valueint<<" / "<<ok->valueint<<" / "<<meh->valueint<<" / "<<miss->valueint<<std::endl;
            }

            // Provide beatmap URL.

            std::cout<<"https://osu.ppy.sh/b/"<<bid->valueint<<std::endl;
            
            // Clean up.

            cJSON_Delete(root);
            cJSON_Delete(info);

        }

    }
}
