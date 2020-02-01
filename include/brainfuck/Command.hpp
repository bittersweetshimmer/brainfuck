#pragma once
namespace bf {
  enum class Command {
    IncrementPointer,
    DecrementPointer,
    Increment,
    Decrement,
    Write,
    Read,
    JumpZero,
    JumpNonZero
  };
}
