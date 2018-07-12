extern "C" {
#include <stdint.h>
}

#include "../src/adc.hpp"
#include "lib/catch.hpp"
#include "util/mocked_avr.hpp"

MockedAvrRegisters MockedAvr::registers = MockedAvrRegisters();

SCENARIO("ADC is working properly", "[ADC]") {
  GIVEN("A new Adc object") {
    Adc<MockedAvr> adc;

    WHEN("State is checked after creation") {
      THEN("ADC is enabled") {
        REQUIRE(MockedAvr::is_set(MockedAvr::Adcsra(), MockedAvr::Aden) ==
                true);
      }

      THEN("Free running mode is enabled") {
        REQUIRE(MockedAvr::is_set(MockedAvr::Adcsra(), MockedAvr::Adfr) ==
                true);
      }

      THEN("Reference voltage equals AVcc with C at AREF pin") {
        REQUIRE(MockedAvr::is_set(MockedAvr::Admux(), MockedAvr::Refs0) ==
                true);
      }

      THEN("ADC interrupts are enabled") {
        REQUIRE(MockedAvr::is_set(MockedAvr::Adcsra(), MockedAvr::Adie) ==
                true);
      }

      THEN("Prescaler is correctly set to /2") {
        REQUIRE(MockedAvr::is_cleared(MockedAvr::Adcsra(),
                                      MockedAvr::Adps2 | MockedAvr::Adps1 |
                                          MockedAvr::Adps0) == true);
      }

      THEN("ADC register is adjusted to simplify usage of 8 bit data") {
        REQUIRE(MockedAvr::is_set(MockedAvr::Admux(), MockedAvr::Adlar) ==
                true);
      }
    }

    WHEN("ADC is stopped") {
      adc.stop_ADC();

      THEN("ADEN is 0") {
        REQUIRE(MockedAvr::is_cleared(MockedAvr::Adcsra(), MockedAvr ::Aden));
      }
    }

    WHEN("ADC is started") {
      adc.start_ADC();

      THEN("ADEN is 1") {
        REQUIRE(MockedAvr::is_set(MockedAvr::Adcsra(), MockedAvr::Aden));
      }
    }

    WHEN("ADC conversion ends") {
      MockedAvr::set(MockedAvr::Adcsra(), MockedAvr::Adif);
      MockedAvr::set(MockedAvr::Adch(), 100);

      THEN("Result can be obtained from ADCH") {
        REQUIRE(MockedAvr::Adch() == 100);
      }

      THEN("ADC conversion complete flag is set if global interrupts are enabled") {
        //TODO
        REQUIRE(MockedAvr::is_set(MockedAvr::Adcsra(), MockedAvr::Adif));
      }
    }
  }
}