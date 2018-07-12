#ifndef MEASURE_HPP
#define MEASURE_HPP

#include "adc.hpp"
#include "usart.hpp"
#include "util/fifo.hpp"
#include "util/avr.hpp"

template <uint16_t BufferSize>
class Measure {
 public:
  /**
   * @brief Flushes buffer to USART buffer, queueing it to be sent
   *
   * @param usart an Usart reference
   */
  void flush_data_via_USART(Usart& usart) {
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
  inline bool is_full() const { return buffer.is_full(); }

  /**
   * @brief Stores provided data in buffer
   *
   * @param data
   */
  inline void store_measured_data(const uint8_t data) { buffer.put(data); }

 private:
  FifoQueue<BufferSize> buffer;
  const Adc<Avr> adc;
};

#endif  // MEASURE_HPP