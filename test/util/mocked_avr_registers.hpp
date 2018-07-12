#ifndef MOCKED_AVR_REGISTERS_HPP
#define MOCKED_AVR_REGISTERS_HPP

extern "C" {
#include <stdint.h>
}

class MockedAvrRegisters {
 public:
  uint8_t Admux = 0;
  uint8_t Adcsra = 0;
  uint8_t Adch = 0;
};

#endif  // MOCKED_AVR_REGISTERS_HPP