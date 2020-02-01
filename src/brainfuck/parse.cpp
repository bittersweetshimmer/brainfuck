#include <brainfuck/parse.hpp>

bf::Program* bf::parse(const char* source) {
  bf::Program* head = nullptr;
  bf::Program* value = nullptr;

  for (auto i = 0; source[i] != '\0'; ++i) {
    auto maybe_command = bf::parse_command(source[i]);

    if (maybe_command.has_value()) {
      if (value == nullptr) {
        value = new bf::Program{ .value = maybe_command.value() };
        head = value; 
      }
      else {
        value->next = new bf::Program{ .value = maybe_command.value() };
        value->next->previous = value;
        value = value->next;
      }
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

  return bf::util::Maybe<bf::Command>::none();
}

