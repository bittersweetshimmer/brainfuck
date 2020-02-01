#pragma once
#include <brainfuck/utilities/Maybe.hpp>
#include <brainfuck/Command.hpp>
#include <brainfuck/Program.hpp>

namespace bf {
  bf::util::Maybe<bf::Command> parse_command(char character);
  Program* parse(const char* source);
}
