extern "C" {
#include <stdint.h>
}

#include "../src/measure.hpp"
#include "lib/catch.hpp"
#include "util/mocked_avr.hpp"

SCENARIO("Measurements are correctly saved", "[Measure]") {
  Measure<MockedAvr, 4> measure;
  WHEN("Data is saved to max capacity") {
    REQUIRE(measure.store_measured_data(0) == true);
    REQUIRE(measure.store_measured_data(1) == true);
    REQUIRE(measure.store_measured_data(2) == true);
    REQUIRE(measure.store_measured_data(3) == true);

    THEN("Buffer is full") { REQUIRE(measure.is_buffer_full() == true); }

    THEN("Data can be sent via USART") { }

    THEN("No new data can be saved in buffer") {
      REQUIRE(measure.store_measured_data(4) == false);
    }
  }
}