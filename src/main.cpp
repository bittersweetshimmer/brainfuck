#include <iostream>
#include <brainfuck/brainfuck.hpp>

int main(int argc, char* argv[]) {
  if (argc <= 1) { std::cout << "brainfuck: no input" << std::endl; return 0; }

  auto brainfuck = bf::State{ .program = bf::parse(argv[1]), .input = std::cin, .output = std::cout } ;
  while (brainfuck.step()) {}

  return 0;
}


