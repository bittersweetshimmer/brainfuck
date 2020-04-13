#ifdef _WIN32

#include <brainfuck/utilities/console.hpp>
#include <windows.h>

std::ostream& operator<<(std::ostream& os, const bf::util::console::priv::BoldWhite&) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF);

    return os;
}

std::ostream& operator<<(std::ostream& os, const bf::util::console::priv::Yellow&) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x6);

    return os;
}

std::ostream& operator<<(std::ostream& os, const bf::util::console::priv::Red&) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x4);

    return os;
}

std::ostream& operator<<(std::ostream& os, const bf::util::console::priv::Reset&) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x7);

    return os;
}

#endif