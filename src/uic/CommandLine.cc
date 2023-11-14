#include <iostream>
#include <sstream>
#include <log.hh>
#include "utils/uic/CommandLine.hh"
#include "utils/core/network/Socket.hh"
#include "utils/util/Commons.hh"

namespace Utils{
    namespace UIC{

        void get_code_request(void){
            std::stringstream code;
            std::cout<<"https://osu.ppy.sh/oauth/authorize?client_id=24548&redirect_uri=http://localhost:4000&response_type=code&scope=public+identify"<<std::endl;
            std::cout<<"Please copy the link above to your browser and then click on \"Authorize\" button."<<std::endl;
            code<<Utils::Network::receive_code();
            Utils::Commons::write_file(file_target_Strings[Utils::Commons::CODE],code.str(),"w+");
        }

        std::string get_username(void){
            std::string s;
            basic_get_input("Type in the username(max 15 chars): ",s,(s.length()>15),"Username format error(no more than 15 chars), please type in again.")
            return s;
        }

        struct Utils::Commons::BeatmapSet_Range get_beatmapset_range(void){
            int i;
            struct Utils::Commons::BeatmapSet_Range range={0};
            basic_get_input("Type in if you want to download all of the beatmaps on the list(0 for Yes, 1 for No): ",i,(i<0)||(i>1),"Option format error, please type in again.");
            if(i){
                basic_get_input("Type in the start position of the bplist you want to get(0 for default): ",range.offset,((range.offset>100)||(range.offset<0)),"Offset format error, please type in again.");
                basic_get_input("Type in the end position of the bplist you want to get(100 for default): ",range.limit,((range.limit>range.offset)||(range.limit>100)),"Limit format error, please type in again.");

            }
            else{
                range.offset=0;
                range.limit=100;
            }
            return range;
        }

        int get_beatmap_id(void){
            int i;
            basic_get_input("Type in beatmap id: ",i,(i<0),"beatmap id format error, please type in again.");
            return i;
        }
        
        struct Utils::Commons::statistics_mania get_result_info(void){
            struct Utils::Commons::statistics_mania info={0};
            basic_get_input("Type in the count of rainbow 300: ",info.perfect,(info.perfect<0),"Count format error, please type in again.");
            basic_get_input("Type in the count of yellow 300: ",info.great,(info.great<0),"Count format error, please type in again.");
            basic_get_input("Type in the count of 200: ",info.good,(info.good<0),"Count format error, please type in again.");
            basic_get_input("Type in the count of 100: ",info.ok,(info.ok<0),"Count format error, please type in again.");
            basic_get_input("Type in the count of 50: ",info.meh,(info.meh<0),"Count format error, please type in again.");
            basic_get_input("Type in the count of miss: ",info.miss,(info.miss<0),"Count format error, please type in again.");
            basic_get_input("Type in the Star Rating of the beatmap: ",info.sr,(info.sr<0),"Count format error, please type in again.");
            return info;
        }

        cJSON* get_essential_mods(void){
            int ez,nf;
            basic_get_input("Type in the if you have applied EZ mod(0 stands for no, 1 for yes): ",ez,((ez<0)||(ez>1)),"Input format error, please type in again.");
            basic_get_input("Type in the if you have applied NF mod(0 stands for no, 1 for yes): ",nf,((nf<0)||(nf>1)),"Input format error, please type in again.");
            cJSON* mods=cJSON_CreateArray();

            if(ez){
                cJSON* ez_obj=cJSON_CreateString("EZ");
                cJSON_AddItemToArray(mods,ez_obj);
            }
            if(nf){
                cJSON* nf_obj=cJSON_CreateString("NF");
                cJSON_AddItemToArray(mods,nf_obj);
            }

            return mods;
        }
        
        int menu_select(void){
            int select;
            
            std::cout<<std::endl;

            std::cout<<"Type in number to select a function."<<std::endl;
            std::cout<<"1. Get Mapsets from Best Plays of anyone."<<std::endl;
            std::cout<<"2. Get Bpht of yourself."<<std::endl;
            std::cout<<"3. Get Score of a specified beatmap of yourself."<<std::endl;
            std::cout<<"4. Get Score of your recently passed beatmap"<<std::endl;
            std::cout<<"5. Get Score of your recently played beatmap."<<std::endl;
            std::cout<<"6. Get Bpht of anyone."<<std::endl;
            std::cout<<"7. Get Score of a specified beatmap of anyone."<<std::endl;
            std::cout<<"8. Get Score of other's recently passed beatmap."<<std::endl;
            std::cout<<"9. Get Score of other's recently played beatmap."<<std::endl;
            std::cout<<"10.Calculate pp of any beatmap.(Currently mania only)"<<std::endl;
            std::cout<<"99.Set your ID and default game mode."<<std::endl;
            std::cout<<"0. Quit."<<std::endl;
            
            basic_get_input("Your selection: ",select,((select<0)||(select>99)),"Selection error, please type in again.");

            std::cout<<std::endl;
            return select;
        }
        
    }
}
