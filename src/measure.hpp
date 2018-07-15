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
    disable_measurements();
    while (!buffer.is_empty()) {
      usart.send_byte(buffer.get());
    }
    enable_measurements();
  }

  /**
   * @brief Checks if internal buffer is full
   *
   * @return true
   * @return false
   */
  inline bool is_buffer_full() const { return buffer.is_full(); }

  /**
   * @brief Checks if internal buffer is empty
   *
   * @return true
   * @return false
   */
  inline bool is_buffer_empty() const { return buffer.is_empty(); }

  /**
   * @brief Stores provided data in internal buffer
   *
   * @param data
   * @return true if succeded
   * @return false otherwise
   */
  inline bool store_measured_data(uint8_t data) { return buffer.put(data); }

  /**
   * @brief Get the measured data from ADC
   *
   * @return uint8_t
   */
  inline uint8_t get_measured_data() {
    return adc.get_8bit_conversion_result();
  }
  /**
   * @brief Disables ADC
   *
   */
  inline void disable_measurements() const { adc.stop_ADC(); }

  /**
   * @brief Enables ADC
   *
   */
  inline void enable_measurements() const { adc.start_ADC(); }

 private:
  /**
   * @brief Buffer used to store measurements results
   *
   */
  volatile FifoQueue<uint8_t, BufferSize> buffer;

  /**
   * @brief An ADC object
   *
   */
  const Adc<HW> adc;
};

#endif  // MEASURE_HPP