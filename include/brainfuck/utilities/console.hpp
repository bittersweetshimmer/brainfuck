#ifndef _WIN32

namespace bf::util::console {
    constexpr const char* reset = "\033[0m";
    constexpr const char* bold_white = "\033[1;37m";
    constexpr const char* yellow = "\033[0;33m";
    constexpr const char* red = "\033[0;31m";
}

#else
#include <iostream>

namespace bf::util::console {
    namespace priv {
        struct Reset {};
        struct BoldWhite {};
        struct Yellow {};
        struct Red {};
    }

    constexpr auto bold_white = priv::BoldWhite{};
    constexpr auto reset = priv::Reset{};
    constexpr auto yellow = priv::Yellow{};
    constexpr auto red = priv::Red{};
}


std::ostream& operator<<(std::ostream& os, const bf::util::console::priv::BoldWhite&);
std::ostream& operator<<(std::ostream& os, const bf::util::console::priv::Yellow&);
std::ostream& operator<<(std::ostream& os, const bf::util::console::priv::Red&);
std::ostream& operator<<(std::ostream& os, const bf::util::console::priv::Reset&);

#endif