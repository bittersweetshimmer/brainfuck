#pragma once
#include <brainfuck/utilities/DoublyLinkedList.hpp>
#include <brainfuck/ParsedCommand.hpp>

namespace bf {
  using Program = bf::util::DoublyLinkedList<bf::ParsedCommand>;
}
