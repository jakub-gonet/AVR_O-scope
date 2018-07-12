#ifndef AVR_HPP
#define AVR_HPP

extern "C" {
#include <avr/io.h>
}

class Avr {
 public:
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
    return !(address & value);
  }

  // members

  constexpr static volatile uint8_t& Admux() { return ADMUX; }
  constexpr static volatile uint8_t& Adcsra() { return ADCSRA; }
  constexpr static volatile uint8_t& Adch() { return ADCH; }
  constexpr static uint8_t Refs0 = (1 << REFS0);
  constexpr static uint8_t Adlar = (1 << ADLAR);
  constexpr static uint8_t Aden = (1 << ADEN);
  constexpr static uint8_t Adfr = (1 << ADFR);
  constexpr static uint8_t Adsc = (1 << ADSC);
  constexpr static uint8_t Adif = (1 << ADIF);
  constexpr static uint8_t Adie = (1 << ADIE);

 private:
  Avr() {}
  ~Avr() {}
};

#endif  // AVR_HPP