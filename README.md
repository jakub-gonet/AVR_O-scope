# AVR Oscilloscope

This project is created in order to allow gathering some analog data from circuits by the atmega uCs.

It's doing this by doing continous ADC conversion and writing results to internal buffer.
When buffer is full, conversion is stopped and data is send via USART.

This project is written in C++ with HAL which covers nearly entire AVR internals (besides interrupts handlers).

## Compiling

```
cd O-scope
avr-gcc -Os -Wall -std=c++17 -DF_CPU=1000000 -mmcu=atmega8 ./src/main.cpp -o ./bin/main.elf
avr-objcopy -j .text -j .data -O ihex ./bin/main.elf ./bin/main.hex
avrdude -p m8 -c usbasp  -e -U flash:w:./bin/main.hex
```

## Running tests

```
cd O-scope
g++ ./test/lib/main_test.cpp -c //this may take a long time, but it's needed only once
g++ ./test/lib/main_test.o ./test/adc_test.cpp -o ./test/tests && ./test/tests
```