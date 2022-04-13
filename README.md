[![Foo](https://img.shields.io/badge/Version-1.0-brightgreen.svg?style=flat-square)](#versions)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD$%E2%82%AC%20%D0%9D%D0%B0%20%D0%BF%D0%B8%D0%B2%D0%BE-%D1%81%20%D1%80%D1%8B%D0%B1%D0%BA%D0%BE%D0%B9-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)

# GyverJoy
Библиотека для удобной работы с аналоговым джойстиком
- Работает с 10 бит АЦП (0.. 1023)
- Виртуальный режим с внешним значением 10 бит
- Инверсия
- Калибровка нуля
- Мёртвая зона с линеаризацией значения
- "Экспонента" для более плавного контроля
- Оптимизированные вычисления
- Вход: 0.. 1023
- Выход: -255.. 255

### Совместимость
Совместима со всеми Arduino платформами (используются Arduino-функции)

## Содержание
- [Установка](#install)
- [Инициализация](#init)
- [Использование](#usage)
- [Пример](#example)
- [Версии](#versions)
- [Баги и обратная связь](#feedback)

<a id="install"></a>
## Установка
- Библиотеку можно найти по названию **GyverJoy** и установить через менеджер библиотек в:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Скачать библиотеку](https://github.com/GyverLibs/GyverJoy/archive/refs/heads/main.zip) .zip архивом для ручной установки:
    - Распаковать и положить в *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Распаковать и положить в *C:\Program Files\Arduino\libraries* (Windows x32)
    - Распаковать и положить в *Документы/Arduino/libraries/*
    - (Arduino IDE) автоматическая установка из .zip: *Скетч/Подключить библиотеку/Добавить .ZIP библиотеку…* и указать скачанный архив
- Читай более подробную инструкцию по установке библиотек [здесь](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

<a id="init"></a>
## Инициализация
```cpp
GyverJoy joy;           // виртуальный режим
GyverJoy joy(pin);      // с указанием пина АЦП
```

<a id="usage"></a>
## Использование
```cpp
void setPin(uint8_t npin);      // указать пин
void invert(bool ninv);         // инвертировать (true)
void setPeriod(uint8_t nprd);   // период опроса (по умолч. 10 мс)
void calibrate();               // калибровать "ноль" с пина
void calibrate(int val);        // калибровать "ноль" внешним значением
void deadzone(int ndead);       // установить мёртвую зону в единицах АЦП
void exponent(uint8_t nmode);   // настроить экспоненту GJ_LINEAR (умолч.), GJ_SQUARE и GJ_CUBIC или цифрами 0, 1 и 2
bool tick();                    // тикер, вызывать в цикле. Опрос по своему таймеру. Вернёт true после чтения
int compute(int adc);           // ручной опрос внешним значением
int value();                    // получить последнее значение -255.. 255
```
![demo](/docs/demo.png)

### Обычный режим
Укажи пин при инициализации и вызывай `tick()` в `loop()`. По встроенному таймеру джойстик будет 
опрашиваться, значение можно забрать из `value()`. Также `tick()` вернёт `true`, если произошло вычисление.

### Виртуальный режим
При инициализации указывать пин не нужно. Для вычисления передай внешнее значение (0.. 1023) в `compute()`. Функция вернёт результат соответственно настройкам.

### Настройки
- `invert` инвертирует направление джойстика
- `calibrate` читает *текущее* значение сигнала и считает его за "ноль" джойстика
- `deadzone` устанавливает мёртвую зону, но значения пересчитываются и линейность сохраняется
- `exponent` задаёт "экспоненциальное" преобразование значения для более плавного управления

`deadzone` и `exponent` можно использовать совместно! Экспонента будет считаться от краёв мёртвой зоны.

<a id="example"></a>
## Пример
### Бортовой АЦП
```cpp
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
```

### Виртуальный режим
```cpp
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
```

<a id="versions"></a>
## Версии
- v1.0

<a id="feedback"></a>
## Баги и обратная связь
При нахождении багов создавайте **Issue**, а лучше сразу пишите на почту [alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
Библиотека открыта для доработки и ваших **Pull Request**'ов!
