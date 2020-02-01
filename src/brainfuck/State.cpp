#include <brainfuck/State.hpp>

bf::State::~State() {
  if (this->cells != nullptr) delete this->cells;
  if (this->program != nullptr) delete this->program;
}

bool bf::State::step() {
  if (this->program == nullptr) return false;
  auto command = this->program->value;
  
  switch (command) {
    case bf::Command::Increment:
      if (this->cells == nullptr) this->cells = new bf::Cells{ .value = 0u };
      this->cells->value++;
      break;
    case bf::Command::Decrement:
      if (this->cells == nullptr) this->cells = new bf::Cells{ .value = 0u };
      this->cells->value--;
      break;
    case bf::Command::IncrementPointer:
      if (this->cells->next == nullptr) this->cells->next = new bf::Cells{ .value = 0u, .previous = this->cells };
      this->cells = this->cells->next;
      break;
    case bf::Command::DecrementPointer:
      if (this->cells->previous == nullptr) this->cells->previous = new bf::Cells{ .value = 0u, .next = this->cells };
      this->cells = this->cells->previous;
      break;
    case bf::Command::Write:
      this->output << this->cells->value;
      break;
    case bf::Command::Read:
      this->input >> this->cells->value;
      break;
    case bf::Command::JumpZero:
      if (this->cells->value == 0) {
        auto current = this->program->next;
        auto matching_depth = 0;

        while (true) {
          if (current == nullptr) break;

          if (current->value == bf::Command::JumpNonZero) {
            if (matching_depth > 0) {
              matching_depth -= 1;
            }
            else {
              this->program = current->next;
              return true;
            }
          }
          else if (current->value == bf::Command::JumpZero) {
            matching_depth += 1;
          }

          current = current->next;
        }

        return false;
      }
      break;
    case bf::Command::JumpNonZero:
      if (this->cells->value != 0) {
        auto current = this->program->previous;
        auto matching_depth = 0;

        while (true) {
          if (current == nullptr) break;

          if (current->value == bf::Command::JumpZero) {
            if (matching_depth > 0) {
              matching_depth -= 1;
            }
            else { 
              this->program = current->next;
              return true;
            }
          }
          else if (current->value == bf::Command::JumpNonZero) {
            matching_depth += 1;
          }

          current = current->previous;
        }

        return false;
      }
      break;
  }

  this->program = this->program->next;
  return true;
}
