/*
    Библиотека для работы с аналоговой клавиатурой
    GitHub: https://github.com/GyverLibs/AnalogKey
    - Встроенный простенький дебаунс
    - Оптимальный опрос пина по таймеру
    - Проверка конкретной кнопки или вывод номера нажатой
    
    AlexGyver, alex@alexgyver.ru
    https://alexgyver.ru/
    MIT License
    
    v1.0
*/

#ifndef _GyverJoy_h
#define _GyverJoy_h
#include <Arduino.h>

#define GJ_LINEAR 0
#define GJ_SQUARE 1
#define GJ_CUBIC 2

class GyverJoy {
public:
    // инициализация, можно указать пин
    GyverJoy(uint8_t npin = 255) {
        pin = npin;
    }
    
    // указать пин
    void setPin(uint8_t npin) {
        pin = npin;
    }
    
    // инвертировать (true)
    void invert(bool ninv) {
        inv = ninv;
    }
    
    // период опроса (по умолч. 10 мс)
    void setPeriod(uint8_t nprd) {
        prd = nprd;
    }
    
    // калибровать "ноль" с пина
    void calibrate() {
        if (pin != 255) zero = analogRead(pin);
    }
    
    // калибровать "ноль" внешним значением
    void calibrate(int val) {
        zero = val;
    }
    
    // установить мёртвую зону
    void deadzone(int ndead) {
        dead = ndead / 2;
    }
    
    // настроить экспоненту GJ_LINEAR (умолч.), GJ_SQUARE и GJ_CUBIC или цифрами 0, 1 и 2
    void exponent(uint8_t nmode) {
        mode = nmode;
    }
    
    // тикер, вызывать в цикле. Опрос по своему таймеру
    bool tick() {
        if ((uint16_t)((uint16_t)millis() - tmr) >= prd) {
            tmr = millis();
            if (pin != 255) compute(analogRead(pin));
            return true;
        }
        return false;
    }
    
    // ручной опрос внешним значением
    int compute(int adc) {
        val = adc;
        if (val < zero - dead) val = (val - zero + dead) * 255L / (zero - dead);
        else if (val > zero + dead) val = (val - zero - dead) * 255L / (1023 - zero - dead);
        else val = 0;
        if (inv) val = - val;
        if (mode == GJ_LINEAR) return val;

        bool neg = (val < 0) ? 1 : 0;
        if (neg) val = -val;
        if (mode == GJ_SQUARE) val = ((uint32_t)(val + 1) * val) >> 8;
        else val = ((uint32_t)(val + 1) * (val + 1) * val) >> 16;
        if (neg) val = -val;
        return val;
    }
    
    // получить значение -255.. 255
    int value() {
        return val;
    }

private:
    bool inv = 0;
    uint8_t pin, mode = GJ_LINEAR;
    int val = 0;
    int zero = 512, dead = 0;
    uint8_t prd = 10;
    uint16_t tmr = 0;
};

#endif
