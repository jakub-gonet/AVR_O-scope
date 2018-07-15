#ifndef ADC_HPP
#define ADC_HPP

template <class HW>
class Adc {
 public:
  inline Adc() {
    HW::set(HW::DdrC(), 0xFF);
    // First pin used as input, rest as output
    HW::clear(HW::DdrC(), HW::Pc0);

    // Uref = AVCC with external capacitor at AREF pin,
    // ADLAR for convienient 8bit access
    HW::set(HW::Admux(), HW::Refs0 | HW::Adlar | HW::Mux2 | HW::Mux0);

    // ADC enable, free running mode, start first
    // conversion, interrupt on update, turn on interrups,
    // ADC prescaler (/8)
    HW::set(HW::Adcsra(),
            HW::Adps0 | HW::Adps1 | HW::Aden | HW::Adfr | HW::Adie);
  }

  /**
   * @brief Get the 8bit ADC conversion result
   *
   * @return uint8_t
   */
  inline uint8_t get_8bit_conversion_result() const { return HW::Adch(); }

  /**
   * @brief Disables ADC
   *
   */
  inline void stop_ADC() const { HW::clear(HW::Adcsra(), HW::Aden); }

  /**
   * @brief Enables ADC and start a conversion
   *
   */
  inline void start_ADC() const {
    HW::update(HW::Adcsra(), HW::Aden | HW::Adsc);
  }
};

#endif  // ADC_HPP