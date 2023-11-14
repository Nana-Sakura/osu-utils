#ifndef Token_hh
#define Token_hh

#include <string>
#include "utils/util/Commons.hh"

namespace Utils{
    namespace Op{
        
        std::string get_token(int token_type);
        std::string read_token(int token_type);
        void write_token(int token_type,const std::string& token_string);
        
    }
}

#endif /* Token_hh */