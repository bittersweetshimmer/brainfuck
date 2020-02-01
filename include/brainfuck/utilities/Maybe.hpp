#pragma once
#include <utility>

namespace bf::util {
    template<typename T>
    struct Maybe {
    public:
      constexpr Maybe(T&& value);
      constexpr Maybe();

      constexpr bool has_value() const;
      constexpr T& value();
      constexpr const T& value() const;

      constexpr static Maybe<T> none();
    private:
      struct empty {};
      union {
        empty _empty;
        T _value;
      };
      bool _has_value;
    };
}

template<typename T>
constexpr bf::util::Maybe<T> bf::util::Maybe<T>::none() { return Maybe<T>(); }

template<typename T>
constexpr bf::util::Maybe<T>::Maybe(T&& value) : _value(std::forward<T>(value)), _has_value(true) {}

template<typename T>
constexpr bf::util::Maybe<T>::Maybe() : _has_value(false) {}

template<typename T>
constexpr bool bf::util::Maybe<T>::has_value() const { return this->_has_value; }

template<typename T>
constexpr T& bf::util::Maybe<T>::value() { return this->_value; }

template<typename T>
constexpr const T& bf::util::Maybe<T>::value() const { return this->_value; }
