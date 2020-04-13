#include <iostream>
#include <brainfuck/brainfuck.hpp>
#include <brainfuck/utilities/console.hpp>

int main(int argc, char* argv[]) {
  if (argc <= 1) { std::cout << bf::util::console::bold_white << "brainfuck" << bf::util::console::reset << ": no input" << std::endl; return EXIT_SUCCESS; }
  for (int i = 0; i < argc; ++i) {
    std::cout << argv[i] << std::endl;
  }
  return bf::State(bf::parse(argv[1])).run();
}