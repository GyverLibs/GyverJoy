#include <GyverJoy.h>
GyverJoy jx;   // виртуальный джойстик

void setup() {
  Serial.begin(9600);
  //jx.invert(true);  // инвертировать
  // калибровка внешним значением
  jx.calibrate(analogRead(0));
  jx.deadzone(30);  // мёртвая зона
  jx.exponent(GJ_CUBIC);  // экспонента для плавности
}

void loop() {
  // передаём аналоговый сигнал с любого источника
  int value = jx.compute(analogRead(0));
  Serial.println(value);
  delay(10);
}
