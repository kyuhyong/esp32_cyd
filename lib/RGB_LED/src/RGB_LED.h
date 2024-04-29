#ifndef _RGB_LED_H_
#define _RGB_LED_H_

#include <Arduino.h>

class LED
{
public: 
    LED(uint8_t pin);
    LED(uint8_t pin, bool pullup);
    ~LED(){};
    void on();
    void off();
    void pwm(uint8_t);
    void set(uint8_t);
private:
    bool    _isPullup;
    uint8_t _pin;
};

class RGB_LED
{
public:
    RGB_LED(uint8_t pin_R, uint8_t pin_G, uint8_t pin_B)
        : pLedR(new LED(pin_R)), 
        pLedG(new LED(pin_G)), 
        pLedB(new LED(pin_B)) {
    };
    RGB_LED(uint8_t pin_R, uint8_t pin_G, uint8_t pin_B, bool pullup)
        : pLedR(new LED(pin_R, pullup)), 
        pLedG(new LED(pin_G, pullup)), 
        pLedB(new LED(pin_B, pullup)) {
    };
    ~RGB_LED(){};
	
    void set_rgb(uint8_t r, uint8_t g, uint8_t b);

    void update();
    LED* pLedR;
    LED* pLedG;
    LED* pLedB;
private:
    uint16_t _interval_ms;
};

#endif