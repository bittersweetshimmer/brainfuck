#include <brainfuck/State.hpp>
#include <brainfuck/utilities/console.hpp>

bf::State::State(bf::Program* program, std::istream& input, std::ostream& output) :
  program(program), input(input), output(output), cells(new bf::Cells{ .value = 0u }) {}

bf::State::~State() {
  if (this->cells != nullptr) delete this->cells;
  if (this->program != nullptr) delete this->program;
}

int bf::State::run() {
  auto step_info = bf::State::StepInfo { .result = bf::State::StepResult::Continue, .command = bf::util::none };

  do {
    step_info = this->step();
  }
  while (step_info.result == bf::State::StepResult::Continue);

  switch (step_info.result) {
    case bf::State::StepResult::End:
      return EXIT_SUCCESS;

    case bf::State::StepResult::AllocationError:
      std::cerr << bf::util::console::bold_white << "brainfuck" << bf::util::console::reset << ": " << bf::util::console::red << "Memory allocation error";
      if (step_info.command.has_value())
        std::cerr << ": line " << step_info.command.value().line << ", column " << step_info.command.value().column; 
      std::cerr << bf::util::console::reset << std::endl;

      return EXIT_FAILURE;

    case bf::State::StepResult::InvalidJump:
      std::cerr << bf::util::console::bold_white << "brainfuck" << bf::util::console::reset << ": " << bf::util::console::red << "Invalid jump";
      if (step_info.command.has_value())
        std::cerr << ": line " << step_info.command.value().line << ", column " << step_info.command.value().column; 
      std::cerr << bf::util::console::reset << std::endl;

      return EXIT_FAILURE;
  }

  return EXIT_FAILURE;
}

bf::State::StepInfo bf::State::step() {
  if (this->program == nullptr) return { .result = bf::State::StepResult::End, .command = bf::util::none };

  auto parsed_command = this->program->value;
  
  try {
    switch (parsed_command.command) {
      case bf::Command::Increment:
        this->cells->value++;
        break;
      case bf::Command::Decrement:
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
            if (current == nullptr) return { .result = bf::State::StepResult::InvalidJump, .command = bf::util::some(std::move(parsed_command)) };

            if (current->value.command == bf::Command::JumpNonZero) {
              if (matching_depth == 0) {
                this->program = current->next;
                return { .result = bf::State::StepResult::Continue, .command = bf::util::some(std::move(parsed_command)) };
              }

              matching_depth -= 1;
            }
            else if (current->value.command == bf::Command::JumpZero) {
              matching_depth += 1;
            }

            current = current->next;
          }
        }
        break;
      case bf::Command::JumpNonZero:
        if (this->cells->value != 0) {
          auto current = this->program->previous;
          auto matching_depth = 0;

          while (true) {
            if (current == nullptr) return { .result = bf::State::StepResult::InvalidJump, .command = bf::util::some(std::move(parsed_command)) };

            if (current->value.command == bf::Command::JumpZero) {
              if (matching_depth == 0) {
                this->program = current->next;
                return { .result = bf::State::StepResult::Continue, .command = bf::util::some(std::move(parsed_command)) };
              }

              matching_depth -= 1;
            }
            else if (current->value.command == bf::Command::JumpNonZero) {
              matching_depth += 1;
            }

            current = current->previous;
          }
        }
        break;
    }
  }
  catch (std::bad_alloc& err) {
    return { .result = bf::State::StepResult::AllocationError, .command = bf::util::some(std::move(parsed_command)) };
  }

  this->program = this->program->next;
  
  return { .result = bf::State::StepResult::Continue, .command = bf::util::some(std::move(parsed_command)) };
}
