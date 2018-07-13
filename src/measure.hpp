#ifndef MEASURE_HPP
#define MEASURE_HPP

#include "adc.hpp"
#include "usart.hpp"
#include "util/fifo.hpp"

template <class HW, uint16_t BufferSize>
class Measure {
 public:
  /**
   * @brief Flushes buffer to USART buffer, queueing it to be sent
   *
   * @param usart an Usart reference
   */
  void flush_data_via_USART(Usart<HW>& usart) {
    while (!buffer.is_empty()) {
      usart.send_byte(buffer.get());
    }
  }

  /**
   * @brief Checks if internal buffer is full
   *
   * @return true
   * @return false
   */
  inline bool is_buffer_full() const { return buffer.is_full(); }

  /**
   * @brief Stores provided data in buffer
   *
   * @param data
   */
  inline void store_measured_data(const uint8_t data) { buffer.put(data); }

  inline uint8_t get_ADC_result() const {
    return adc.get_8bit_conversion_result();
  }

  inline void disableAdc() const { adc.stop_ADC(); }
  inline void enableAdc() const { adc.start_ADC(); }

 private:
  FifoQueue<BufferSize> buffer;
  const Adc<HW> adc;
};

#endif  // MEASURE_HPP