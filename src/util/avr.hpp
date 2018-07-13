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

  static inline void enable_interrupts() { sei(); }
  static inline void disable_interrupts() { cli(); }

  // members

  constexpr static uint64_t F_cpu = F_CPU;

  // ADC
  constexpr static volatile uint8_t& Admux() { return ADMUX; }
  constexpr static volatile uint8_t& Adcsra() { return ADCSRA; }
  constexpr static volatile uint16_t& Adc() { return ADC; }
  constexpr static volatile uint8_t& Adch() { return ADCH; }

  constexpr static uint8_t Refs0 = (1 << REFS0);
  constexpr static uint8_t Adlar = (1 << ADLAR);
  constexpr static uint8_t Aden = (1 << ADEN);
  constexpr static uint8_t Adfr = (1 << ADFR);
  constexpr static uint8_t Adsc = (1 << ADSC);
  constexpr static uint8_t Adif = (1 << ADIF);
  constexpr static uint8_t Adie = (1 << ADIE);
  constexpr static uint8_t Adps0 = (1 << ADPS0);
  constexpr static uint8_t Adps1 = (1 << ADPS1);

  // USART
  constexpr static volatile uint8_t& Ubrrh() { return UBRRH; }
  constexpr static volatile uint8_t& Ubrrl() { return UBRRL; }
  constexpr static volatile uint8_t& Ucsra() { return UCSRA; }
  constexpr static volatile uint8_t& Ucsrb() { return UCSRB; }
  constexpr static volatile uint8_t& Ucsrc() { return UCSRC; }
  constexpr static volatile uint8_t& Udr() { return UDR; }

  constexpr static uint8_t Rxcie = (1 << RXCIE);
  constexpr static uint8_t Txen = (1 << TXEN);
  constexpr static uint8_t Rxen = (1 << RXEN);
  constexpr static uint8_t Ursel = (1 << URSEL);
  constexpr static uint8_t Ucsz0 = (1 << UCSZ0);
  constexpr static uint8_t Ucsz1 = (1 << UCSZ1);
  constexpr static uint8_t Udrie = (1 << UDRIE);
  constexpr static uint8_t Udre = (1 << UDRE);

 private:
  Avr() {}
  ~Avr() {}
};

#endif  // AVR_HPP