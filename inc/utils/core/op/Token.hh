#ifndef Token_hh
#define Token_hh

#include "utils/util/Commons.hh"
#include <string>

namespace Utils
{
    namespace Op
    {

        std::string get_token(int token_type);
        std::string read_token(int token_type);
        void write_token(int token_type, const std::string& token_string);

    }// namespace Op
}// namespace Utils

#endif /* Token_hh */