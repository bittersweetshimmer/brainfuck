#include <iostream>
#include <brainfuck/parse.hpp>

bf::Program* bf::parse(const char* source) {
  bf::Program* head = nullptr;
  bf::Program* value = nullptr;

  auto current_column = 1u;
  auto current_line = 1u;

  for (auto i = 0; source[i] != '\0'; ++i) {
    auto maybe_command = bf::parse_command(source[i]);

    if (maybe_command.has_value()) {
      if (value == nullptr) {
        value = new bf::Program{ .value = { .command = maybe_command.value(), .column = current_column, .line = current_line } };
        head = value; 
      }
      else {
        value->next = new bf::Program{ .value = { .command = maybe_command.value(), .column = current_column, .line = current_line } };
        value->next->previous = value;
        value = value->next;
      }
    }
    else {
      std::cerr << "\033[1:37m" << "brainfuck" << "\033[0m" << ": " << "\x1B[33m" << "Unknown symbol \'"
        << source[i] << "\': line " << current_line << ", column " << current_column
        << "\033[0m\n";
    }

    if (source[i] == '\n') {
      current_line += 1;
      current_column = 1;
    }
    else {
      current_column += 1;
    }
  }

  return head;
}

bf::util::Maybe<bf::Command> bf::parse_command(char character) {
  switch (character) {
    case '>': return bf::Command::IncrementPointer;
    case '<': return bf::Command::DecrementPointer;
    case '+': return bf::Command::Increment;
    case '-': return bf::Command::Decrement;
    case '.': return bf::Command::Write;
    case ',': return bf::Command::Read;
    case '[': return bf::Command::JumpZero;
    case ']': return bf::Command::JumpNonZero;
  }

  return bf::util::none;
}

