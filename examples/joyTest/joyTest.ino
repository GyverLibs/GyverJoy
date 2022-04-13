#include <GyverJoy.h>
GyverJoy jx(0);   // джойстик на пине 0

void setup() {
  Serial.begin(9600);
  //jx.invert(true);  // инвертировать
  jx.calibrate();   // калибровка нуля при запуске
  jx.deadzone(30);  // мёртвая зона
  jx.exponent(GJ_CUBIC);  // экспонента для плавности
}

void loop() {
  // тикер опрашивает АЦП по своему таймеру
  if (jx.tick()) {
    // выводим значение
    Serial.println(jx.value());
  }
}
