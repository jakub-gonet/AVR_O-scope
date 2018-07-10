#ifndef MEASURE_HPP
#define MEASURE_HPP

#include "adc.hpp"
#include "usart.hpp"

template <uint16_t BufferSize>
class Measure {
 public:
  /**
   * @brief Flushes buffer to USART buffer, queueing it to be sent
   *
   * @param usart an Usart reference
   */
  void flush_data_via_USART(Usart& usart) {
    for (; last_value == 0 || last_value % BufferSize; ++last_value) {
      usart.send_byte(buffer[last_value]);
    }

    last_value = 0;
  }

  /**
   * @brief Checks if internal buffer is full
   *
   * @return true
   * @return false
   */
  inline bool is_full() const { return last_value + 1 == BufferSize; }

  /**
   * @brief Stores provided data in buffer
   *
   * @param data
   */
  inline void store_measured_data(const uint8_t data) { buffer[last_value++]; }

 private:
  uint16_t last_value = 0;
  uint8_t buffer[BufferSize];
  const Adc<> adc;
};

#endif  // MEASURE_HPP