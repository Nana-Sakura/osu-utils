#ifndef CommandLine_hh
#define CommandLine_hh

#include <string>
#include "utils/util/Commons.hh"

#define basic_get_input(notice,var,condition,err_notice)                                            \
                            std::cout<<notice;                                                      \
                            std::cin>>var;                                                          \
                            while(condition||std::cin.fail()){                                      \
                                LOG(err_notice);                                                    \
                                std::cout<<notice;                                                  \
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');  \
                            }


namespace Utils{
    namespace UIC{

        void get_code_request(void);
        
        std::string get_username(void);
        
        struct Utils::Commons::BeatmapSet_Range get_beatmapset_range(void);

        int get_beatmap_id(void);

        struct Utils::Commons::statistics_mania get_result_info(void);

        cJSON* get_essential_mods(void);

        int menu_select(void);

    }
}

#endif /* CommandLine_hh */
