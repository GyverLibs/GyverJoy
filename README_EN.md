This is an automatic translation and may be incorrect in some places. See the source README and examples for authoritative information.

[![latest](https://img.shields.io/github/v/release/GyverLibs/GyverJoy.svg?color=brightgreen)](https://github.com/GyverLibs/GyverJoy/releases/latest/download/GyverJoy.zip)
[![PIO](https://badges.registry.platformio.org/packages/gyverlibs/library/GyverJoy.svg)](https://registry.platformio.org/libraries/gyverlibs/GyverJoy)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD%24%E2%82%AC%20%D0%9F%D0%BE%D0%B4%D0%B4%D0%B5%D1%80%D0%B6%D0%B0%D1%82%D1%8C-%D0%B0%D0%B2%D1%82%D0%BE%D1%80%D0%B0-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/GyverJoy?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# GyverJoy
Library for easy work with analog joystick
- Works with 10 bit ADC (0..1023)
- Virtual mode with an external value of 10 bits
- Inversion
- Zero calibration
- Dead Zone with Linearization of Value
- Exponent for smoother control
- Optimized computing
- Entrance: 0. 1023.
- Exit: -255. 255

### Compatibility
Compatible with all Arduino platforms (Arduino features are used)

## Contents
- [Installation](#install)
- [Use of use](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="usage"></a>

## Use of use
### GyverJoyVirt
```cpp
GyverJoyVirt joy;   // virtualization
```
```cpp
// invert (silent false)
void invert(bool ninv);

// set the survey period (by omission. 10 ms)
void setPeriod(uint8_t nprd);

// calibrate the "zero" external value n
void calibrate(uint16_t val);

// dead- zone
void deadzone(uint8_t ndead);

// configure the exponent: GJ_LINEAR (default), GJ_SQUARE, or GJ_CUBIC
void exponent(GJTYPE nmode);

// ticker, call in the loop. Poll on your own timer
bool tick();

// hand-examination n
int16_t compute(uint16_t adc);

// get a value of -255. 255
int16_t value();
```

### GyverJoy
```cpp
GyverJoy joy(pin);  // pin-marked
```
```cpp
// invert (silent false)
void invert(bool ninv);

// set the survey period (by omission. 10 ms)
void setPeriod(uint8_t nprd);

// calibrate the "zero" external value n
void calibrate(uint16_t val);

// dead- zone
void deadzone(uint8_t ndead);

// configure the exponent: GJ_LINEAR (default), GJ_SQUARE, or GJ_CUBIC
void exponent(GJTYPE nmode);

// pin
void setPin(uint8_t npin);

// calibrate zero from pin
void calibrate();

// Read from the pin and make a calculation
int16_t compute();

// ticker, call in the loop. Pin poll on his own timer
bool tick();

// get a value of -255. 255
int16_t value();
```

![demo](/docs/demo.png)

### Regular regime
Point the pin at initialization and call`tick()`into`loop()`. On the built-in timer joystick will be
The value can be taken from the`value()`. Also.`tick()`return`true`If there's been a calculation.

### Virtual mode
When initializing, you do not need to specify a pin. To calculate, transfer the external value (0..1023) to`compute()`. The function will return the result according to the settings.

### Settings
- `invert`invert
- `calibrate`reads the *current* value of the signal and counts it as "zero" joystick
- `deadzone`establishes a dead zone, but values are recalculated and linearity is maintained
- `exponent`specifies an “exponential” value conversion for smoother control

`deadzone`and`exponent`It can be shared! The exhibit will be counted from the edges of the dead zone.

<a id="example"></a>

## Example
### Airborne ADC
```cpp
#include <GyverJoy.h>
GyverJoy jx(0);  // joystick

void setup() {
    Serial.begin(9600);
    // jx.invert(true); invert
    jx.calibrate();         // zero-calibration
    jx.deadzone(30);        // dead-zone
    jx.exponent(GJ_CUBIC);  // exponent
}

void loop() {
    // ticker polls ADC on its timer
    if (jx.tick()) {
        // point out
        Serial.println(jx.value());
    }
}
```

### Virtual mode
```cpp
#include <GyverJoy.h>
GyverJoyVirt jx;  // joystick

void setup() {
    Serial.begin(9600);
    // jx.invert(true); invert
    //  calibration n
    jx.calibrate(analogRead(0));
    jx.deadzone(30);        // dead-zone
    jx.exponent(GJ_CUBIC);  // exponent
}

void loop() {
    // transmitting an analog signal from any source
    int value = jx.compute(analogRead(0));
    Serial.println(value);
    delay(10);
}

```

<a id="versions"></a>
## Versions
- v1.0
- v1.1 - reverse calibration corrected, cubic gamma corrected at zero signal

<a id="install"></a>

## Installation
- The library can be found under the name **GyverJoy** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download the library](https://github.com/GyverLibs/GyverJoy/archive/refs/heads/main.zip).zip archive for manual installation:
    - Unpack and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unpack and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/ *
    - (Arduino IDE) Automatic installation from .zip: *Sketch/Connect library/Add .ZIP library...* and specify downloaded archive
- Read more detailed instructions for installing libraries[here](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: new versions fix errors and bugs, as well as optimize and add new features.
- Through the library manager IDE: find the library as when installing and click "Update"
- Manually: **Delete the folder with the old version** and then put the new one in its place. “Replacement” can not be done: sometimes new versions delete files that will remain when replaced and can lead to errors!

<a id="feedback"></a>

## Bugs and feedback
If you find bugs, create **Issue**, or better write to the mail immediately.[alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
The library is open for revision and your **Pull Requests*!

When reporting bugs or incorrect work of the library, it is necessary to specify:
- Library version
- What is used by the IC
- SDK version (for ESP)
- Arduino IDE version
- Are embedded examples that use features and designs that cause bugs in your code working correctly?
- What code was downloaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed. Not a canvas of a thousand lines, but a minimum code.
