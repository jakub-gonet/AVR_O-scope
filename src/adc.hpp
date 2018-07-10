#ifndef ADC_HPP
#define ADC_HPP

extern "C" {
#include <avr/io.h>
}
#include "util/avr.hpp"

template <class HW = Avr>
class Adc {
 public:
  inline Adc() {
    // Uref = AVCC with external capacitor at AREF pin,
    // set let adjust of result for convienient 8bit access
    HW::set(ADMUX, (1 << REFS0) | (1 << ADLAR));

    // ADC enable, free running mode, start first
    // conversion, interrupt on update, turn on
    // interrupts default prescaler (/2)
    HW::set(ADCSRA, (1 << ADEN) | (1 << ADFR) | (1 << ADSC) | (1 << ADIF) |
                        (1 << ADIE));
  }
};

#endif  // ADC_HPP