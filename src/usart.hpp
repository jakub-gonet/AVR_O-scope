#ifndef USART_HPP
#define USART_HPP

#include "util/fifo.hpp"

template <class HW>
class Usart {
 public:
  /**
   * @brief Construct a new Usart object with specified baud rate
   *
   * @param baud_rate
   */
  inline Usart(const uint16_t baud_rate) {
    const uint16_t baud_prescale = (((HW::F_cpu / (baud_rate * 16UL))) - 1);
    HW::set(HW::Ubrrh(), baud_prescale >> 8);
    HW::set(HW::Ubrrl(), baud_prescale);

    // enable Tx and Rx and enable receive interrupts
    HW::set(HW::Ucsrb(), HW::Rxcie | HW::Txen | HW::Rxen);

    // set data format to 8 bits, 1 stop bit, no parity check
    HW::set(HW::Ucsrc(), HW::Ursel | HW::Ucsz0 | HW::Ucsz1);
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
    if (data != static_cast<uint8_t>(-1)) {
      HW::set(HW::Udr(), data);
    } else {
      disable_transmit_buffer_empty_interrupts();
    }
  }

  /**
   * @brief Function designed to be used in ISR(USART_RXC_vect).
   *
   */
  inline void receive_data_via_interrupt() { received.put(HW::Udr()); }

 private:
  /**
   * @brief FIFO queue used to buffer data to send
   *
   */
  volatile FifoQueue<uint8_t, 32> to_send;
  /**
   * @brief FIFO queue used to buffer received data
   *
   */
  volatile FifoQueue<uint8_t, 32> received;

  /**
   * @brief Start the proccess of sending data from `to_send` queue. It should
   * end after reaching delimiter or if queue is empty
   *
   */
  inline void start_sending_data() const {
    wait_until_transmit_buffer_is_ready();
    enable_transmit_buffer_empty_interrupts();
  }

  /**
   * @brief Waits until UDR can be written
   *
   */
  inline void wait_until_transmit_buffer_is_ready() const {
    while (HW::is_cleared(HW::Ucsra(), HW::Udre))
      ;
  }
  /**
   * @brief Enables transmitter interrupts
   *
   */
  inline void enable_transmit_buffer_empty_interrupts() const {
    HW::update(HW::Ucsrb(), HW::Udrie);
  }

  /**
   * @brief Disables buffer empty interrupts
   *
   */
  inline void disable_transmit_buffer_empty_interrupts() const {
    HW::clear(HW::Ucsrb(), HW::Udrie);
  }
};

#endif  // USART_HPP