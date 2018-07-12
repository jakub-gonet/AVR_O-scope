#ifndef USART_HPP
#define USART_HPP

extern "C" {
#include <avr/io.h>
}
#include "util/fifo.hpp"

class Usart {
 public:
  /**
   * @brief Construct a new Usart object with specified baud rate
   *
   * @param baud_rate
   */
  inline Usart(const uint16_t baud_rate) {
    const uint16_t baud_prescale = (((F_CPU / (baud_rate * 16UL))) - 1);
    UBRRH = (baud_prescale >> 8);
    UBRRL = baud_prescale;

    // enable Tx and Rx and enable receive interrupts
    UCSRB = (1 << RXCIE) | (1 << TXEN) | (1 << RXEN);

    // set data format to 8 bits, 1 stop bit, no parity check
    UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
  }

  /**
   * @brief Sends only one byte at time
   *
   * @param byte data to send
   */
  void send_byte(const uint8_t byte) {
    while (!to_send.put(byte))
      ;
    start_sending_data();
  }

  /**
   * @brief Sends string by queueing data in FIFO queue
   *
   * @param string
   */
  void send_string(char const* const string) {
    uint8_t data;
    uint16_t i = 0;
    while ((data = static_cast<uint8_t>(string[i++]))) {
      for (bool started = false; !to_send.put(data);) {
        if (!started) {
          start_sending_data();
          started = true;
        }
      }
    }

    start_sending_data();
  }

  /**
   * @brief Returns only one byte at time
   *
   * @return uint8_t received data
   */
  uint8_t receive_byte() {
    while (received.is_empty())
      ;
    return received.get();
  }

  /**
   * @brief Receives string by taking data from queue
   * `\r` should end the sent string
   *
   * @param buffer
   * @param buffer_size
   * @return char*
   */
  char* receive_string(char* const buffer, uint16_t buffer_size) {
    uint16_t i = 0;
    while (i < buffer_size - 1) {
      while (received.is_empty())
        ;

      uint8_t data = received.get();
      buffer[i++] = data;
      if (data == '\r') {
        break;
      }
    }
    buffer[i] = '\0';
    return buffer;
  }

  /**
   * @brief Function designed to be used in ISR(USART_UDRE_vect).
   *
   */
  inline void send_data_via_interrupt() {
    uint8_t data = to_send.get();
    if (data != static_cast<uint8_t>(-1) && data) {
      UDR = data;
    } else {
      disable_transmit_buffer_empty_interrupts();
    }
  }

  /**
   * @brief Function designed to be used in ISR(USART_RXC_vect).
   *
   */
  inline void receive_data_via_interrupt() { received.put(UDR); }

 private:
  /**
   * @brief FIFO queue used to buffer data to send
   *
   */
  volatile FifoQueue<32> to_send;
  /**
   * @brief FIFO queue used to buffer received data
   *
   */
  volatile FifoQueue<32> received;

  /**
   * @brief Start the proccess of sending data from `to_send` queue. It should
   * end after reaching delimiter or if queue is empty
   *
   */
  inline void start_sending_data() const {
    wait_until_transmit_buffer_is_ready();
    enable_transmit_buffer_empty_interrupts();
  }

  inline void wait_until_transmit_buffer_is_ready() const {
    while (!(UCSRA & (1 << UDRE)))
      ;
  }
  inline void enable_transmit_buffer_empty_interrupts() const {
    UCSRB |= (1 << UDRIE);
  }

  inline void disable_transmit_buffer_empty_interrupts() const {
    UCSRB &= ~(1 << UDRIE);
  }
};

#endif  // USART_HPP