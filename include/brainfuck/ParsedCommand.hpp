#include <brainfuck/Command.hpp>

namespace bf {
    struct ParsedCommand {
        bf::Command command;
        
        unsigned int column;
        unsigned int line;
    };
}