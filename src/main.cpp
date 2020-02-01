#include <iostream>
#include <brainfuck/brainfuck.hpp>

int main(int argc, char* argv[]) {
  if (argc <= 1) { std::cout << "\033[1:37m" << "brainfuck" << "\033[0m" << ": no input" << std::endl; return EXIT_SUCCESS; }
  else return bf::State(bf::parse(argv[1])).run();
}