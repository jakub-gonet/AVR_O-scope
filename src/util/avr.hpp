#ifndef AVR_HPP
#define AVR_HPP

extern "C" {
#include <avr/io.h>
}

class Avr {
 public:
  static inline volatile uint8_t& get(volatile uint8_t& address) {
    return address;
  }

  static inline void set(volatile uint8_t& address, const uint8_t value) {
    address = value;
  }

  static inline void clear(volatile uint8_t& address, const uint8_t value) {
    address &= ~value;
  }

 private:
  Avr() {}
  ~Avr() {}
};

#endif  // AVR_HPP