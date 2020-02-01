#pragma once
#include <istream>
#include <ostream>
#include <brainfuck/Cells.hpp>
#include <brainfuck/Program.hpp>

namespace bf {
  struct State final {
    ~State();

    bool step();

    Cells* cells = nullptr;
    Program* program = nullptr;

    std::istream& input;
    std::ostream& output;
  };
};
