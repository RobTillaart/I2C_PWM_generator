
[![Arduino CI](https://github.com/RobTillaart/I2C_PWM_generator/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/I2C_PWM_generator/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/I2C_PWM_generator/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/I2C_PWM_generator/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/I2C_PWM_generator/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/I2C_PWM_generator.svg)](https://github.com/RobTillaart/I2C_PWM_generator/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/I2C_PWM_generator/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/I2C_PWM_generator.svg?maxAge=3600)](https://github.com/RobTillaart/I2C_PWM_generator/releases)

```
not used.
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/I2C_PWM_generator.svg)](https://registry.platformio.org/libraries/robtillaart/I2C_PWM_generator)
```

# I2C_PWM_generator

Arduino UNO as a 6 channel I2C PWM generator


## Version: 0.1.0

## Description

** Experimental**

I2C_PWM_generator is a sketch to change an Arduino UNO in an I2C slave device
to control the 6 PWM outputs of the Arduino UNO. 

One can think of this sketch as a co-processor that handles the 6 PWM channels
independent of a main processor. The sketch was written after a question on GitHub
for a library for the PCA9632 device (which has more features than this sketch.
It allows to set the duty cycle of the PWM signals from 0..255 = 0..100%.

The start up default is 0% for all 6 channels.

My test UNO has a frequency of ~975 Hz and ~489 Hz depending on TIMER used.

The sketch is simple but not tested to the extreme.

Typical application is to control the intensity of 6 LEDs or one RGB LED.

Feedback as always is welcome.


### I2C

The sketch has a fixed I2C address of **0x30**. (adjust if needed)
**Pin 4** is used as an address pin to select between I2C address **0x30** and **0x31**.

The default speed of the device is 100 KHz.
One need to adapt the code of the sketch to adjust the speed.


### PWM

THe PWM pins of the Arduino UNO are:

```
int PWMpins[6] = {3, 5, 6, 9, 10, 11};`
```

These are addressed as register 0, 1, 2, 3 etc.


### Commands

The command to set a PWM value from another MCU is straightforward.
It could look like this.

```cpp
#include "Wire.h"

void setPWM(uint8_t port, uint8_t value)
{
  Wire.beginTransmission(0x30);  //  or 0x31
  Wire.write(port);
  Wire.write(value);
  _error = Wire.endTransmission();
}

```

Indicative table of values, (mini scope)

|  value  |  duty cycle  |
|:-------:|:------------:|
|    0    |    0.0 %     |
|    1    |    0.7 %     |
|    5    |    2.3 %     |
|   10    |    4.3 %     |
|   25    |     10 %     |
|   51    |     20 %     |
|   63    |     25 %     |
|  127    |     50 %     |
|  191    |     75 %     |
|  255    |    100 %     |


## Future

#### Must

- update documentation

#### Should

- implement Power On Start Duty Cycle.
  - store / load EEPROM?
- implement **setAllZero()** full stop.

#### Could

- does this sketch need a library to control it from another Arduino?
- more address pins?
- implement **getPWM(port)** read back
- implement **setAllZero()** full stop.
- implement **uptime()** return millis()?
- implement frequency adjust
- implement Power On Start Duty Cycle.
  - store / load EEPROM?
- implement **reset()** to POS
- implement debug / logging over Serial?


#### Wont


## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,

