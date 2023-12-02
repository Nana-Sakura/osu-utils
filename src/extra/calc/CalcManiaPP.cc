#include "utils/extra/calc/CalcManiaPP.hh"
#include "utils/uic/CommandLine.hh"
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>

namespace Utils
{
    namespace Extra
    {
        namespace Calc
        {

            float difficulty(float accpp)
            {
                return (accpp <= 0.8) ? 0 : ((accpp - 0.8) / 0.2);
            }

            float acc_calc(int pft, struct Utils::Commons::statistics_mania i)
            {
                return (float)(perfect_value[pft] * i.perfect + 300 * i.great + 200 * i.good + 100 * i.ok + 50 * i.meh) / (float)(perfect_value[pft] * (i.perfect + i.great + i.good + i.ok + i.meh + i.miss));
            }

            float multiplier(cJSON* mods)
            {
                bool ez = 0;
                bool nf = 0;
                int size = cJSON_GetArraySize(mods);
                for(int i = 0; i < size; i++)
                {
                    if(std::strcmp(cJSON_GetArrayItem(mods, i)->valuestring, "EZ") == 0)
                    {
                        ez = 1;
                    }
                    if(std::strcmp(cJSON_GetArrayItem(mods, i)->valuestring, "NF") == 0)
                    {
                        nf = 1;
                    }
                }
                float ans = 8.0;
                if(ez)
                {
                    ans *= 0.5;
                }
                if(nf)
                {
                    ans *= 0.75;
                }
                return ans;
            }

            float maximumpp(struct Utils::Commons::statistics_mania i, float multiplier)
            {
                float star_rating = i.sr;
                uint32_t notes = i.perfect + i.great + i.good + i.ok + i.meh + i.miss;
                return std::pow(((star_rating > 0.20) ? (star_rating - 0.15) : 0.05), 2.2) * (1.0 + 0.1 * ((notes > 1500) ? 1.0 : ((float)notes / (float)1500))) * multiplier;
            }

            void mania_pp(struct Utils::Commons::statistics_mania i, cJSON* mods)
            {
                float accpp_value = acc_calc(3, i);
                float diff = difficulty(accpp_value);
                float multiplier_value = multiplier(mods);
                float max_pp = maximumpp(i, multiplier_value);

                std::cout << "AccPP: " << std::fixed << std::setprecision(3) << accpp_value * 100 << "%" << std::endl;
                std::cout << "Difficulty: " << std::fixed << std::setprecision(3) << diff * 100 << "%" << std::endl;
                std::cout << "if SS: " << std::fixed << std::setprecision(3) << max_pp << "pp" << std::endl;
                std::cout << "Achieved PP: " << std::fixed << std::setprecision(3) << max_pp * diff << "pp" << std::endl;
            }

            void calc_mania_pp(void)
            {
                struct Utils::Commons::statistics_mania result = Utils::UIC::get_result_info();
                cJSON* mods = Utils::UIC::get_essential_mods();
                mania_pp(result, mods);
                cJSON_Delete(mods);
            }

        }// namespace Calc
    }    // namespace Extra
}// namespace Utils
