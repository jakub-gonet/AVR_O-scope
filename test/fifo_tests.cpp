extern "C" {
#include <stdint.h>
}
#include "../src/util/fifo.hpp"
#include "lib/catch.hpp"

SCENARIO("Data can be inserted to and retrieved from FIFO queue",
         "[FifoQueue]") {
  GIVEN("An empty FIFO queue") {
    FifoQueue<uint8_t, 2> queue;
    REQUIRE(queue.is_empty() == true);

    WHEN("Data is inserted") {
      REQUIRE(queue.put(1) == true);

      THEN("Queue is not empty") { REQUIRE(queue.is_empty() == false); }
      THEN("Data can be retrieved") { REQUIRE(queue.get() == 1); }
    }

    WHEN("Data is inserted and then retrieved") {
      REQUIRE(queue.put(10) == true);
      REQUIRE(queue.put(20) == true);
      REQUIRE(queue.get() == 10);
      REQUIRE(queue.get() == 20);

      THEN("Queue is empty") { REQUIRE(queue.is_empty() == true); }

      THEN("Take function should return -1 indicating retrieval error") {
        REQUIRE(queue.get() == static_cast<uint8_t>(-1));
      }
      THEN("Next values can be inserted") {
        REQUIRE(queue.put(50) == true);
        REQUIRE(queue.put(100) == true);
      }
    }
  }

  GIVEN("A full FIFO queue") {
    FifoQueue<uint8_t, 2> queue;
    REQUIRE(queue.is_empty() == true);
    REQUIRE(queue.put(10) == true);
    REQUIRE(queue.put(20) == true);
    REQUIRE(queue.is_full() == true);

    WHEN("Next item is being inserted") {
      THEN("Push function returns false indicating insert error") {
        REQUIRE(queue.put(1) == false);
      }
    }
  }

  GIVEN("A 0 capacity FIFO queue") {
    FifoQueue<uint8_t, 0> queue;
    REQUIRE(queue.is_empty() == true);
    REQUIRE(queue.is_full() == true);
    WHEN("Next item is being inserted") {
      THEN("Push function returns false indicating insert error") {
        REQUIRE(queue.put(1) == false);
      }
    }

    WHEN("Next item is being taken") {
      THEN("Take function should return -1 indicating retrieval error") {
        REQUIRE(queue.get() == static_cast<uint8_t>(-1));
      }
    }
  }
}