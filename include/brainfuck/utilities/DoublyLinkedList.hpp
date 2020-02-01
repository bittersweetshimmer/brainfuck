#pragma once

namespace bf::util {
    template<typename T>
    struct DoublyLinkedList final {
    public:
      ~DoublyLinkedList<T>();

      T value = T();
      DoublyLinkedList<T>* previous = nullptr;
      DoublyLinkedList<T>* next = nullptr;
    };
}

template<typename T>
bf::util::DoublyLinkedList<T>::~DoublyLinkedList() {
  if (this->next != nullptr) {
    this->next->previous = nullptr;
    delete this->next;
  }
  
  if (this->previous != nullptr) {
    this->previous->next = nullptr;
    delete this->previous;
  }
};
