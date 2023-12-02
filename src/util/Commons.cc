#include <format>
#include <fstream>
#include <iomanip>
#include <log.hh>
#include <sstream>
#include <sys/stat.h>

#include "utils/util/Commons.hh"

namespace Utils
{
    namespace Commons
    {

        std::string read_file(const std::string& path)
        {
            std::ifstream file;
            file.open(path, std::ios::in);
            std::stringstream content;
            std::string var;
            while(file.good())
            {
                file >> var;
                content << var;
            }
            file.close();
            return content.str();
        }

        void write_file(const std::string& path_to_file, const std::string& file_content, const std::string& write_mode)
        {
            std::ofstream output;
            output.open(path_to_file);
            //output.open(path_to_file,std::ios::out|std::ios::trunc|((write_mode.compare("wb"))?0:std::ios::binary));
            output << file_content;
            output.close();
        }

        ssize_t get_file_size(const std::string& path)
        {
            struct stat stat_buf;
            int rc = stat(path.c_str(), &stat_buf);
            return rc == 0 ? stat_buf.st_size : -1;
        }

        time_t get_last_modified_time(const std::string& path)
        {
            struct stat stat_buf;
            int rc = stat(path.c_str(), &stat_buf);
            return rc == 0 ? stat_buf.st_mtime : -1;
        }

        int check_expire(const std::string& path)
        {
            time_t current_time = time(NULL);
            size_t time_delta = current_time - get_last_modified_time(path);
            return (time_delta < 86400) ? 0 : -1;
        }

        int compare(const void* p1, const void* p2)
        {
            return (*(int*)p1) - (*(int*)p2);
        }

        std::string strfsec(int length)
        {
            if((length >= 86400) || (length <= 0))
            {
                LOG("The beatmap is not aimed for humans.");
                exit(16);
            }
            int hrs = length / 3600;
            length %= 3600;
            int min = length / 60;
            length %= 60;
            int vaild_num = 3;
            if(hrs == 0)
            {
                vaild_num--;
            }
            std::stringstream result;
            if(vaild_num == 3)
            {
                result << std::setw(2) << hrs << ":" << std::setfill('0') << std::setw(2) << min << ":" << std::setfill('0') << std::setw(2) << length;
            }
            else
            {
                result << std::setw(2) << min << ":" << std::setfill('0') << std::setw(2) << length;
            }
            return result.str();
        }

        std::string strf_mod_intro(cJSON* mods)
        {
            int mod_count = cJSON_GetArraySize(mods);
            std::stringstream mods_string;
            mods_string << " ";
            if(mod_count)
            {
                mods_string << "+";
                for(int i = 0; i < mod_count; i++)
                {
                    cJSON* mod = cJSON_GetArrayItem(mods, i);
                    mods_string << mod->valuestring << " ";
                }
            }
            return mods_string.str();
        }

        void show_progress(int task_now, int task_sum, int width)
        {
            float progress = (float)task_now / (float)task_sum;
            int end_position = width * progress;
            std::cout << "[";
            for(int i = 0; i < width; i++)
            {
                if(i < end_position)
                {
                    std::cout << "=";
                }
                else if(i == end_position)
                {
                    std::cout << ">";
                }
                else
                {
                    std::cout << " ";
                }
            }
            std::cout << "] " << std::fixed << std::setprecision(1) << progress * 100.0 << "%\r" << std::flush;
        }

        int search_array(const char** array, int len, const std::string& val)
        {
            for(int i = 0; i < len; i++)
            {
                if(val.compare(array[i]) == 0)
                {
                    return i;
                }
            }

            // No result means facing error.
            std::exit(-1);
        }

    }// namespace Commons
}// namespace Utils
