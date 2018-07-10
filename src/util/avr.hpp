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

 private:
  Avr() {}
  ~Avr() {}
};

#endif  // AVR_HPP