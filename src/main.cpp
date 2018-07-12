extern "C" {
#include <avr/interrupt.h>
#include <avr/io.h>
}
#include "measure.hpp"
#include "usart.hpp"

Usart usart(4800);
Measure<16> measure;
int main() {
  sei();
  while (true) {
    if (measure.is_buffer_full()) {
      measure.flush_data_via_USART(usart);
    }
  }
}

ISR(USART_UDRE_vect) {
  measure.disableAdc();
  usart.send_data_via_interrupt();
  measure.enableAdc();
}

// ISR(USART_RXC_vect) {
//   usart.receive_data_via_interrupt();
// }

ISR(ADC_vect) {
  measure.store_measured_data(measure.get_ADC_result());
}