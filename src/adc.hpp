#ifndef ADC_HPP
#define ADC_HPP

template <class HW>
class Adc {
 public:
  inline Adc() {
    // Uref = AVCC with external capacitor at AREF pin,
    // set let adjust of result for convienient 8bit access
    HW::set(HW::Admux(), HW::Refs0 | HW::Adlar);

    // ADC enable, free running mode, start first
    // conversion, interrupt on update, turn on
    // interrupts default prescaler (/2)
    HW::set(HW::Adcsra(), HW::Aden | HW::Adfr | HW::Adsc | HW::Adif | HW::Adie);
  }

  inline uint8_t get_8bit_conversion_result() const { return HW::Adch(); }

  inline void stop_ADC() const { HW::clear(HW::Adcsra(), HW::Aden); }
  inline void start_ADC() const { HW::update(HW::Adcsra(), HW::Aden); }
};

#endif  // ADC_HPP