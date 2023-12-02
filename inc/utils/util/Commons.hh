#ifndef Commons_hh
#define Commons_hh

#include <cJSON.h>
#include <filesystem>
#include <string>

inline const char* osu_mode_Strings[] = {"osu", "taiko", "fruits", "mania"};
inline const char* check_target_Strings[] = {"best", "recent", "firsts"};
inline const char* file_target_Strings[] = {"Cache/acg_token", "Cache/cc_token", "Cache/code", "Cache/user.json"};
inline const char* video_target_Strings[] = {"full", "novideo"};
inline const int perfect_value[] = {300, 305, 315, 320};

namespace Utils
{
    namespace Commons
    {

        struct personal_info {
            uint32_t uid;
            uint32_t mode;
        };

        struct BeatmapSet_Range {
            int offset;
            int limit;
        };

        struct statistics_mania {
            uint32_t perfect;
            uint32_t great;
            uint32_t good;
            uint32_t ok;
            uint32_t meh;
            uint32_t miss;
            double sr;
        };

        struct ranking_analyze {
            int s;
            int sh;
            int x;
            int xh;
            int fc;
            double avgpp;
            double ppmax;
            double ppmin;
        };

        enum osu_mode {
            OSU = 0,
            TAIKO = 1,
            FRUITS = 2,
            MANIA = 3
        };

        enum check_target {
            BEST = 0,
            RECENT = 1,
            FIRSTS = 2
        };

        enum target {
            OTHERS = 0,
            SELF = 1
        };

        enum include_fails {
            EXCLUDES = 0,
            INCLUDES = 1
        };

        enum token_type {
            ACG_TOKEN = 0,
            CC_TOKEN = 1
        };

        enum file_path {
            ACG = 0,
            CC = 1,
            CODE = 2,
            USER = 3
        };

        enum perfect {
            Score_V1 = 0,
            Score_V2 = 1,
            Score_Lazer = 2,
            Score_PP = 3
        };

        std::string read_file(const std::string& path);

        void write_file(const std::string& path_to_file, const std::string& file_content, const std::string& write_mode);

        ssize_t get_file_size(const std::string& path);

        time_t get_last_modified_time(const std::string& path);

        int check_expire(const std::string& path);

        int compare(const void* p1, const void* p2);

        std::string strfsec(int length);

        std::string strf_mod_intro(cJSON* mods);

        void show_progress(int task_now, int task_sum, int width);

        int search_array(const char** array, int len, const std::string& val);

    }// namespace Commons
}// namespace Utils

#endif /* Commons_hh */
