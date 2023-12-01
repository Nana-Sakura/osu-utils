#include <filesystem>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <log.hh>
#include <cJSON.h>

#include "utils/core/network/Download.hh"
#include "utils/util/Commons.hh"


namespace Utils{
    namespace Network{

        void map_downloader(const std::string& score_list,struct Utils::Commons::BeatmapSet_Range range,int request_video){
            
            // Do prepare jobs.

            cJSON* root=cJSON_Parse(score_list.c_str());
            int arraysize=cJSON_GetArraySize(root);
            int* array=new int[arraysize];

            for(int i=0;i<arraysize;i++){
                cJSON* info=cJSON_GetArrayItem(root,i);
                cJSON* beatmap=cJSON_GetObjectItem(info,"beatmap");
                cJSON* siditem=cJSON_GetObjectItem(beatmap,"beatmapset_id");
                array[i]=siditem->valueint;
            }

            cJSON_Delete(root);

            // Will write data to Mapsets Folder.

            if(Utils::Commons::get_file_size("Mapsets")==-1){
                std::filesystem::create_directory("Mapsets",".");
            }

            // To make life easier, sort the items before removing the duplicated.

            int j=1,count;
            qsort(array,arraysize,sizeof(int),Utils::Commons::compare);
            for(int i=1;i<range.limit-range.offset;i++){
                if(array[i]!=array[i-1]){
                    array[j++]=array[i];
                }
            }
            count=j;

            for(int i=0;i<count;i++){

                // Show Progress.
                
                Utils::Commons::show_progress(i,count,70);

                // Download Progress.

                std::stringstream url;
                url<<"https://dl.sayobot.cn/beatmaps/download/"<<video_target_Strings[request_video]<<"/"<<array[i];

                Requests object(url.str(),"","");
                std::string beatmap_object=object.curl_get_object_request();
                
                std::stringstream path;
                path<<"Mapsets/"<<array[i]<<".osz";
                Utils::Commons::write_file(path.str(),beatmap_object,"wb");

            }

            Utils::Commons::show_progress(count,count,70);
            printf("\n");

        }
    }
}
