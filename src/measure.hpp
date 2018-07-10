#ifndef MEASURE_HPP
#define MEASURE_HPP

template <uint16_t BufferSize>
class Measure {
 public:
  inline void store_measured_data(const uint8_t data) { buffer[last_value++]; }

 private:
  uint16_t last_value = 0;
  uint8_t buffer[BufferSize];
};

#endif  // MEASURE_HPP