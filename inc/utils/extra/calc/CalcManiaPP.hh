#ifndef CalcManiaPP_hh
#define CalcManiaPP_hh

#include "utils/util/Commons.hh"
#include <cJSON.h>

namespace Utils
{
    namespace Extra
    {
        namespace Calc
        {

            float difficulty(float accpp);
            float acc_calc(int pft, struct Utils::Commons::statistics_mania i);
            float multiplier(cJSON* mods);
            float maximumpp(struct Utils::Commons::statistics_mania i, float multiplier);
            void mania_pp(struct Utils::Commons::statistics_mania i, cJSON* mods);
            void calc_mania_pp(void);

        }// namespace Calc
    }    // namespace Extra
}// namespace Utils

#endif /* CalcManiaPP_hh */
