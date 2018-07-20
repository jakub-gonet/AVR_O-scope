#ifndef MOCKED_AVR_HPP
#define MOCKED_AVR_HPP

extern "C" {
#include <stdint.h>
}
#include "mocked_avr_registers.hpp"

class MockedAvr {
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

  static inline void update(volatile uint8_t& address, const uint8_t value) {
    address |= value;
  }

  static inline bool is_set(volatile uint8_t& address, const uint8_t value) {
    return address & value;
  }

  static inline bool is_cleared(volatile uint8_t& address,
                                const uint8_t value) {
    return address & ~value;
  }

  // members

  // IO

  static volatile uint8_t& DdrC() { return registers.DdrC; }

  constexpr static uint8_t Pc0 = (1 << 0);
  constexpr static uint8_t Pc1 = (1 << 1);
  constexpr static uint8_t Pc2 = (1 << 2);
  constexpr static uint8_t Pc3 = (1 << 3);
  constexpr static uint8_t Pc4 = (1 << 4);
  constexpr static uint8_t Pc5 = (1 << 5);
  constexpr static uint8_t Pc6 = (1 << 6);

  // ADC

  static volatile uint8_t& Admux() { return registers.Admux; }
  static volatile uint8_t& Adcsra() { return registers.Adcsra; }
  static volatile uint8_t& Adch() { return (registers.Adch); }

  constexpr static uint8_t Mux0 = (1 << 0);
  constexpr static uint8_t Mux1 = (1 << 1);
  constexpr static uint8_t Mux2 = (1 << 2);
  constexpr static uint8_t Mux3 = (1 << 3);
  constexpr static uint8_t Adps2 = (1 << 2);
  constexpr static uint8_t Adps1 = (1 << 1);
  constexpr static uint8_t Adps0 = (1 << 0);
  constexpr static uint8_t Refs0 = (1 << 6);
  constexpr static uint8_t Adlar = (1 << 5);
  constexpr static uint8_t Aden = (1 << 7);
  constexpr static uint8_t Adfr = (1 << 5);
  constexpr static uint8_t Adsc = (1 << 6);
  constexpr static uint8_t Adif = (1 << 4);
  constexpr static uint8_t Adie = (1 << 3);

  static MockedAvrRegisters registers;
};

#endif  // MOCKED_AVR_HPP