#ifndef FIFO_HPP
#define FIFO_HPP
extern "C" {
#include <stdint.h>
}

template <typename T = uint8_t, uint16_t Size = 32>
class FifoQueue {
 public:
  /**
   * @brief Pushes new item to FIFO queue
   *
   * @param byte
   * @return true
   * @return false
   */
  bool put(const T byte) volatile {
    if (!is_full()) {
      ++item_count;
      buffer[(++head) % Size] = byte;
      return true;
    }
    return false;
  }

  /**
   * @brief Returns next element from queue
   *
   * @return uint8_t -1 indicating error
   */
  T get() volatile {
    if (!is_empty()) {
      --item_count;
      return buffer[(++tail) % Size];
    }
    return -1;
  }

  /**
   * @brief Checks if queue is empty
   * 
   * @return true 
   * @return false 
   */
  inline bool is_empty() const volatile { return item_count == 0; }

  /**
   * @brief Checks if queue is full
   * 
   * @return true 
   * @return false 
   */
  inline bool is_full() const volatile { return item_count == Size; }

  /**
   * @brief Clears queue
   *
   */
  void clear_queue() volatile {
    head = -1;
    tail = -1;
    item_count = 0;
  }

 private:
  uint16_t item_count = 0;
  T buffer[Size];
  uint16_t head = -1;
  uint16_t tail = -1;
};

#endif  // FIFO_HPP