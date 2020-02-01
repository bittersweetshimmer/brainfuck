#pragma once

namespace bf::util {
    template<typename T>
    struct List final {
    public:
      ~List<T>();

      T value = T();
      List<T>* previous = nullptr;
      List<T>* next = nullptr;
    };
}

template<typename T>
bf::util::List<T>::~List() {
  if (this->next != nullptr) {
    this->next->previous = nullptr;
    delete this->next;
  }
  
  if (this->previous != nullptr) {
    this->previous->next = nullptr;
    delete this->previous;
  }
};
