extern "C" {
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
}
#include "measure.hpp"
#include "usart.hpp"
#include "util/avr.hpp"

Usart<Avr> usart(4800);
Measure<Avr, 32> measure;

int main() {
  Avr::enable_interrupts();
  while (true) {
    if (measure.is_buffer_full()) {
      measure.flush_data_via_USART(usart);
    }
  }
}

inline void usart_data_register_empty_interrupt() {
  usart.send_data_via_interrupt();
}

inline void adc_conversion_complete_interrupt() {
  measure.store_measured_data();
}

ISR(USART_UDRE_vect) {
  usart_data_register_empty_interrupt();
}

ISR(USART_RXC_vect) {
  usart.receive_data_via_interrupt();
}

ISR(ADC_vect) {
  adc_conversion_complete_interrupt();
}