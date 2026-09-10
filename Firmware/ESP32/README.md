# PMW3389 Library

PMW3389 driver library for ATmega32u4 based boards. e.g. Sparkfun Pro Micro

## Features

- Register Read and Write
- SROM firmware upload
- Motion Burst Reads (dx, dy, motion flag, SQUAL)
- DPI/CPI set and get. Range of 100-16000, steps of 50

## Hardware Requirements

- 1.8v-2.1v to VDD with decoupling capacitors (10uF and 100nF)
- 1.8v-3.6v to VDDIO  with decoupling capacitors (10uF and 100nF)
- SPI connection with correct voltage (1.8v-3.6v (same as voltage to VDDIO))
- 13ohm Resistor then 1.8v-2.1v to LED1_P with decoupling capacitors (10uF and 100nF)
- VDDPIX to ground through decoupling capacitors (10uF and 100nF)
- GND wired to Ground

## Installation

**PlatformIO** - Copy this folder into your project's 'lib/' folder

**ArduinoIDE** - Copy this folder into your sketchbook's 'libraries/' directory (usually 'Documents/Arduino/libraries/'), then restart the IDE.

**OR**
- Download [Library Zip File](https://github.com/aSharcc/PMW3389-Custom-Mouse/releases/download/2.0/Library.zip)
- Go to ArduinoIDE
- Sketch->include Library->Add .ZIP Library...->Select downloaded .ZIP file

## API Reference

| Method | Description |
|---|---|
| `PMW3389(uint8_t ncsPin)` | Constructor. Sets which pin is used for chip select. |
| `bool begin()` | Initializes SPI, resets the sensor, uploads SROM firmware. Returns `true` if Product_ID verification passes. |
| `uint8_t readRegister(uint8_t regAddr)` | Reads a single register. |
| `void writeRegister(uint8_t regAddr, uint8_t value)` | Writes a single register. |
| `PMW3389_Motion readMotion()` | Performs a burst read. Returns a struct with `isMotion`, `dx`, `dy`, `squal`. |
| `void setDPI(uint16_t dpi)` | Sets sensor resolution. Clamped to 100–16000, rounded down to the nearest 50. |
| `uint16_t getDPI()` | Reads back the currently set DPI. |

## Usage

``` cpp
#include <PMW3389.h>

PMW3389 sensor(10); // NCS on pin 10

void setup() {
    if (!sensor.begin()) {
        // SROM upload or Product_ID check failed
        while (1);
    }
    sensor.setDPI(1600);
}

void loop() {
    PMW3389_Motion motion = sensor.readMotion();
    if (motion.isMotion) {
        // motion.dx, motion.dy available here
    }
}
```

See `examples/BasicMouse` for a complete mouse implementation with buttons and scroll.

## License

Licensed under MIT license.
[LICENSE](/LICENSE)
