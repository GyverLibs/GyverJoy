This is an automatic translation, may be incorrect in some places. See sources and examples!

# Gyverjoy
Library for convenient work with an analog joystick
- works with 10 bits of ADC (0 .. 1023)
- virtual mode with an external value of 10 bits
- Inversion
- Calibration of zero
- Dead zone with linarization of the meaning
- "Exhibent" for more smooth control
- Optimized calculations
- Entrance: 0 .. 1023
- Exit: -255 .. 255

## compatibility
Compatible with all arduino platforms (used arduino functions)

## Content
- [installation] (# Install)
- [initialization] (#init)
- [use] (#usage)
- [Example] (# Example)
- [versions] (#varsions)
- [bugs and feedback] (#fedback)

<a id="install"> </a>
## Installation
- The library can be found by the name ** gyverjoy ** and installed through the library manager in:
    - Arduino ide
    - Arduino ide v2
    - Platformio
- [download the library] (https://github.com/gyverlibs/gyverjoy/archive/refs/heads/main.zip) .Zip archive for manual installation:
    - unpack and put in * C: \ Program Files (X86) \ Arduino \ Libraries * (Windows X64)
    - unpack and put in * C: \ Program Files \ Arduino \ Libraries * (Windows X32)
    - unpack and put in *documents/arduino/libraries/ *
    - (Arduino id) Automatic installation from. Zip: * sketch/connect the library/add .Zip library ... * and specify downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%BD%D0%BE%BE%BE%BED0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: errors and bugs are corrected in the new versions, as well as optimization and new features are added
- through the IDE library manager: find the library how to install and click "update"
- Manually: ** remove the folder with the old version **, and then put a new one in its place.“Replacement” cannot be done: sometimes in new versions, files that remain when replacing are deleted and can lead to errors!


<a id="init"> </a>
## initialization
`` `CPP
Gyverjoy Joy;// virtual regime
Gyverjoy Joy (PIN);// indicating Pina ADC
`` `

<a id="usage"> </a>
## Usage
`` `CPP
VOID setpin (uint8_t npin);// Indicate the pin
VOID Invert (Bool Ninv);// Invert (True)
VOID Setperiod (Uint8_T NPRD);// survey period (default 10 ms)
VOID Calibrate ();// calibrate "zero" with Pina
VOID Calibrate (Int Val);// calibrate "zero" external meaning
Void Deadzone (int ndead);// Install the dead zone in ACP units
VOID Exponent (Uint8_t Nmode);// Configure the exponent gj_linear (silent), gj_square and gj_cubic or numbers 0, 1 and 2
Bool Tick ();// ticker, call in the cycle.A survey by its timer.Will return True after reading
int compute (int Adc);// Manual survey by external value
int velue ();// get the last value -255 .. 255
`` `
! [Demo] (/doc/demo.png)

## Original mode
Indicate the pin for initialization and call `tick ()` in `loop ()`.By the built -in timer, the joystick will
To be interpreted, the value can be taken from `velue ()`.Also `tick ()` will return `true` if the calculation occurred.

### virtual mode
In case of initialization, it is not necessary to indicate a pin.For calculation, transferexternal value (0 .. 1023) in `compute ()`.The function will return the result according to the settings.

### Settings
- `Invert
- `Calibrate` reads * current * signal value and considers it for" zero "joystick
- `Deadzone` sets the dead area, but values are recalculated and linearity is preserved
- `Exponent` sets the" exponential "transformation of the value for more smooth control

`Deadzone` and` Exponent` can be used together!The exponent will be considered from the edges of the dead zone.

<a id="EXAMPLE"> </a>
## Example
## board ADC
`` `CPP
#include <gyverjoy.h>
Gyverjoy JX (0);// joystick on pin 0

VOID setup () {
  Serial.Begin (9600);
  //jx.invertration);// Invert
  jx.calibrate ();// Calibration of zero at launch
  JX.deadzone (30);// dead zone
  jx.exponent (gj_cubic);// Exhibitment for smoothness
}

VOID loop () {
  // ticker interviews ADC according to its timer
  if (jx.tick ()) {
    // We display the meaning
    Serial.println (jx.value ());
  }
}
`` `

### virtual mode
`` `CPP
#include <gyverjoy.h>
Gyverjoy JX;// Virtual joystick

VOID setup () {
  Serial.Begin (9600);
  //jx.invertration);// Invert
  // Calibration by external value
  JX.Calibrate (ANALOGREAD (0));
  JX.deadzone (30);// dead zone
  jx.exponent (gj_cubic);// Exhibitment for smoothness
}

VOID loop () {
  // We transmit an analog signal from any source
  int velue = jx.compute (analogread (0));
  Serial.println (value);
  Delay (10);
}
`` `

<a id="versions"> </a>
## versions
- V1.0

<a id="feedback"> </a>
## bugs and feedback
Create ** Issue ** when you find the bugs, and better immediately write to the mail [alex@alexgyver.ru] (mailto: alex@alexgyver.ru)
The library is open for refinement and your ** pull Request ** 'ow!


When reporting about bugs or incorrect work of the library, it is necessary to indicate:
- The version of the library
- What is MK used
- SDK version (for ESP)
- version of Arduino ide
- whether the built -in examples work correctly, in which the functions and designs are used, leading to a bug in your code
- what code has been loaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed.Not a canvas of a thousand lines, but a minimum code