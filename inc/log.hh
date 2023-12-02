#ifndef log_hh
#define log_hh

#include <iostream>
#include <sstream>

#define LOG(text)                                                        \
    {                                                                    \
        std::stringstream s;                                             \
        s << "[" << __FILE__ << ":" << __LINE__ << "] " << text << "\n"; \
        std::cout << s.str();                                            \
    }

#endif /* log_hh */
