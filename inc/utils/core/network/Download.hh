#ifndef Download_hh
#define Download_hh

#include "utils/core/network/Requests.hh"
#include "utils/util/Commons.hh"

namespace Utils
{
    namespace Network
    {

        void map_downloader(const std::string& score_list, struct Utils::Commons::BeatmapSet_Range range, int request_video);

    }
}// namespace Utils

#endif /* Download_hh */
