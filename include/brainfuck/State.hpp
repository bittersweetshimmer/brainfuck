#pragma once
#include <iostream>
#include <brainfuck/utilities/Maybe.hpp>
#include <brainfuck/Cells.hpp>
#include <brainfuck/Program.hpp>

namespace bf {
  struct State final {
    State(Program* = nullptr, std::istream& = std::cin, std::ostream& = std::cout);
    ~State();

    enum class StepResult {
      AllocationError,
      InvalidJump,
      Continue,
      End
    };

    struct StepInfo {
      StepResult result;
      bf::util::Maybe<bf::ParsedCommand> command;
    };

    StepInfo step();
    int run();

private:
    Cells* cells = nullptr;
    Program* program = nullptr;

    std::istream& input;
    std::ostream& output;
  };
};
