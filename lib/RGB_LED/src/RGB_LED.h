#ifndef _RGB_LED_H_
#define _RGB_LED_H_

#include <Arduino.h>

class LED
{
public: 
    typedef enum {
        LED_STATE_NORMAL = 0,
        LED_STATE_BLINK,
        LED_STATE_STROBE,
    }LED_STATE;
    LED(uint8_t pin);
    LED(uint8_t pin, bool pullup);
    ~LED(){};
    void on();
    void off();
    void pwm(uint8_t);
    void set(uint8_t);
    void blink(uint16_t, uint16_t);
    void update(void);
private:
    bool    _isPullup;
    bool    _isOn;
    uint8_t _pin;
    LED_STATE _current_state;
    uint16_t _on_ms;
    uint16_t _off_ms;
    uint32_t _next_ms;
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