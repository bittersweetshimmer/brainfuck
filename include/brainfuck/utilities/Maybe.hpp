#pragma once
#include <utility>

namespace bf::util {
    struct NoneType {};

    constexpr static auto none = NoneType{};

    template<typename T>
    struct Maybe {
    public:
      constexpr Maybe(T&& value);
      constexpr Maybe(NoneType);

      constexpr bool has_value() const;
      constexpr T& value();
      constexpr const T& value() const;
    private:
      struct empty {};
      union {
        empty _empty;
        std::decay_t<T> _value;
      };
      bool _has_value;
    };

    template<typename T>
    constexpr Maybe<std::decay_t<T>> some(T&& value);
}

template<typename T>
constexpr bf::util::Maybe<std::decay_t<T>> bf::util::some(T&& value) {
  return bf::util::Maybe<std::decay_t<T>>(std::forward<T>(value));
}

template<typename T>
constexpr bf::util::Maybe<T>::Maybe(T&& value) : _value(std::forward<T>(value)), _has_value(true) {}

template<typename T>
constexpr bf::util::Maybe<T>::Maybe(bf::util::NoneType) : _has_value(false) {}

template<typename T>
constexpr bool bf::util::Maybe<T>::has_value() const { return this->_has_value; }

template<typename T>
constexpr T& bf::util::Maybe<T>::value() { return this->_value; }

template<typename T>
constexpr const T& bf::util::Maybe<T>::value() const { return this->_value; }
