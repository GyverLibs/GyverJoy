#pragma once
#include <Arduino.h>

enum GJTYPE : uint8_t {
    GJ_LINEAR,
    GJ_SQUARE,
    GJ_CUBIC,
};

class GyverJoyVirt {
   public:
    // инвертировать (умолч. false)
    void invert(bool ninv) {
        inv = ninv;
    }

    // установить период опроса (по умолч. 10 мс)
    void setPeriod(uint8_t nprd) {
        prd = nprd;
    }

    // калибровать "ноль" внешним значением
    void calibrate(uint16_t val) {
        zero = val;
    }

    // установить мёртвую зону
    void deadzone(uint8_t ndead) {
        dead = ndead / 2;
    }

    // настроить экспоненту GJ_LINEAR (умолч.), GJ_SQUARE или GJ_CUBIC
    void exponent(GJTYPE nmode) {
        mode = nmode;
    }

    // тикер, вызывать в цикле. Опрос по своему таймеру
    bool tick() {
        if (uint8_t(uint8_t(millis()) - tmr) >= prd) {
            tmr = millis();
            return true;
        }
        return false;
    }

    // ручной опрос внешним значением
    int16_t compute(uint16_t adc) {
        if (adc + dead < zero) val = int16_t(adc - zero + dead) * 255L / (zero - dead);
        else if (adc > zero + dead) val = (adc - zero - dead) * 255L / (1023 - zero - dead);
        else val = 0;
        if (inv) val = -val;
        if (mode == GJ_LINEAR) return val;

        int16_t nval = abs(val);
        if (mode == GJ_SQUARE) nval = (uint32_t(nval + 1) * nval) >> 8;
        else nval = (uint32_t(nval + 1) * (nval + 1) * nval) >> 16;
        val = val < 0 ? -nval : nval;
        return val;
    }

    // получить значение -255.. 255
    int16_t value() {
        return val;
    }

   private:
    uint16_t zero = 512;
    int16_t val = 0;
    GJTYPE mode = GJ_LINEAR;
    uint8_t dead = 0;
    uint8_t prd = 10, tmr = 0;
    bool inv = 0;
};

class GyverJoy : public GyverJoyVirt {
   public:
    // инициализация, можно указать пин
    GyverJoy(uint8_t npin) {
        pin = npin;
    }

    // указать пин
    void setPin(uint8_t npin) {
        pin = npin;
    }

    // калибровать "ноль" с пина
    void calibrate() {
        GyverJoyVirt::calibrate(analogRead(pin));
    }

    // прочитать с пина и сделать расчёт
    int16_t compute() {
        return GyverJoyVirt::compute(analogRead(pin));
    }

    // тикер, вызывать в цикле. Опрос пина по своему таймеру
    bool tick() {
        if (GyverJoyVirt::tick()) {
            compute();
            return true;
        }
        return false;
    }

   private:
    uint8_t pin;
};
