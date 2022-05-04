This is an automatic translation, may be incorrect in some places. See sources and examples!

# GyverJoy
Library for convenient work with an analog joystick
- Works with 10bit ADC (0..1023)
- Virtual mode with 10 bit external value
- Inversion
- Zero calibration
- Dead zone with value linearization
- "Expo" for smoother control
- Optimized calculations
- Input: 0.. 1023
- Output: -255.. 255

### Compatibility
Compatible with all Arduino platforms (using Arduino functions)

## Content
- [Install](#install)
- [Initialization](#init)
- [Usage](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found by the name **GyverJoy** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download Library](https://github.com/GyverLibs/GyverJoy/archive/refs/heads/main.zip) .zip archive for manual installation:
    - Unzip and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unzip and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/*
    - (Arduino IDE) automatic installation from .zip: *Sketch/Include library/Add .ZIP library…* and specify the downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE% D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

<a id="init"></a>
## Initialization
```cpp
Gyver Joy joy; // virtual mode
GyverJoy joy(pin); // indicating the ADC pin
```

<a id="usage"></a>
## Usage
```cpp
void setPin(uint8_t npin); // specify pin
void invert(bool ninv); // invert (true)
void setPeriod(uint8_t nprd); // polling period (default 10 ms)
void calibrate(); // calibrate "zero" from pin
void calibrate(int val); // calibrate "zero" with an external value
void deadzone(int ndead); // set deadzone in ADC units
void exponent(uint8_t nmode); // set the exponent of GJ_LINEAR (default), GJ_SQUARE and GJ_CUBIC or numbers 0, 1 and 2
bool tick(); // ticker, call in a loop. Poll on your own timer. Will return true after reading
int compute(int adc); // manual polling with an external value
intvalue(); // get last value -255.. 255
```
![demo](/docs/demo.png)

### Normal mode
Specify a pin during initialization and call `tick()` in `loop()`. According to the built-in timer, the joystick will
be interrogated, the value can be taken from `value()`. Also `tick()` will return `true` if a calculation has occurred.

### Virtual mode
You do not need to specify a pin during initialization. To calculate, pass an external value (0.. 1023) to `compute()`. The function will return the result according to the settings.

### Settings
- `invert` inverts the direction of the joystick
- `calibrate` reads the *current* value of the signal and treats it as joystick "zero"
- `deadzone` sets deadzone, but values ​​are recalculated and linearity is preserved
- `exponent` specifies "exponential" value conversion for smoother control

`deadzone` and `exponent` can be used together! The exponent will be calculated from the edges of the dead zone.

<a id="example"></a>
## Example
### Onboard ADC
```cpp
#include <GyverJoy.h>
GyverJoy jx(0); // joystick on pin 0

void setup() {
  Serial.begin(9600);
  //jx.invert(true); // invert
  jx.calibrate(); // zero calibration at startup
  jx.deadzone(30); // dead zone
  jx.exponent(GJ_CUBIC); // exponent for smoothness
}

void loop() {
  // the ticker polls the ADC on its own timer
  if (jx.tick()) {
    // output value
    Serial.println(jx.value());
  }
}
```

### Virtual mode
```cpp
#include <GyverJoy.h>
GyverJoy jx; // virtual joystick

void setup() {
  Serial.begin(9600);
  //jx.invert(true); // invert
  // calibration with an external value
  jx.calibrate(analogRead(0));
  jx.deadzone(30); // dead zone
  jx.exponent(GJ_CUBIC); // exponent for smoothness
}

void loop() {
  // transmit an analog signal from any source
  int value = jx.compute(analogRead(0));
  Serial println(value);
  delay(10);
}
```

<a id="versions"></a>
## Versions
- v1.0

<a id="feedback"></a>
## Bugs and feedback
When you find bugs, create an **Issue**, or better, immediately write to the mail [alex@alexgyver.ru](mailto:alex@alexgyver.ru)
The library is open for revision and your **Pull Request**'s!