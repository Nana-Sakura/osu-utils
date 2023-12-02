#include <cJSON.h>
#include <log.hh>
#include <string>

#include "utils/core/auth/AuthorizationCodeGrant.hh"
#include "utils/core/op/Query.hh"
#include "utils/core/op/Token.hh"
#include "utils/core/profile/AccountProfile.hh"
#include "utils/uic/CommandLine.hh"

namespace Utils
{
    namespace Profile
    {

        struct Utils::Commons::personal_info query_info(const std::string& cc_token)
        {
            std::string username = Utils::UIC::get_username();
            std::string info_json = Utils::Op::get_personal_info(username, cc_token);
            return parse_info(info_json);
        }

        struct Utils::Commons::personal_info query_self_info(void)
        {
            std::string acg_token = Utils::Op::get_token(Utils::Commons::ACG);
            std::string info_json = Utils::Op::get_own_personal_info(acg_token);
            return parse_info(info_json);
        }

        struct Utils::Commons::personal_info parse_info(const std::string& info_json)
        {
            struct Utils::Commons::personal_info info = {0};
            cJSON* root = cJSON_Parse(info_json.c_str());
            cJSON* uid = cJSON_GetObjectItem(root, "id");
            cJSON* mode = cJSON_GetObjectItem(root, "playmode");

            if(uid == NULL)
            {
                LOG("Invaild user info, please check your network status.");
            }
            else
            {
                info.uid = uid->valueint;
                info.mode = Utils::Commons::search_array(osu_mode_Strings, 4, mode->valuestring);
            }

            cJSON_Delete(root);
            return info;
        }

        struct Utils::Commons::personal_info read_info(void)
        {
            struct Utils::Commons::personal_info result = {0};
            std::string info = Utils::Commons::read_file(file_target_Strings[Utils::Commons::USER]);
            cJSON* root = cJSON_Parse(info.c_str());
            cJSON* uid = cJSON_GetObjectItem(root, "uid");
            cJSON* mode = cJSON_GetObjectItem(root, "mode");
            result.uid = uid->valueint;
            result.mode = mode->valueint;
            cJSON_Delete(root);
            return result;
        }

        void write_user_info(struct Utils::Commons::personal_info info)
        {
            cJSON* root = cJSON_CreateObject();
            cJSON_AddNumberToObject(root, "uid", info.uid);
            cJSON_AddNumberToObject(root, "mode", info.mode);
            char* json = cJSON_Print(root);
            Utils::Commons::write_file(file_target_Strings[Utils::Commons::USER], json, "w+");
            free(json);
            cJSON_Delete(root);
        }

        struct Utils::Commons::personal_info get_info(int info_type, const std::string& cc_token)
        {
            if(info_type == Utils::Commons::SELF)
            {
                if(Utils::Commons::get_file_size(file_target_Strings[Utils::Commons::USER]) == -1)
                {
                    struct Utils::Commons::personal_info result = {0};
                    result = query_self_info();
                    write_user_info(result);
                    return result;
                }
                else
                {
                    return read_info();
                }
            }
            else
            {
                return query_info(cc_token);
            }
        }

    }// namespace Profile
}// namespace Utils
