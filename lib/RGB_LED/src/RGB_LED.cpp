#include "RGB_LED.h"

/// @brief Initialize LED pin default pull-up state
/// @param pin IO PIN
LED::LED(uint8_t pin){
    _pin = pin;
    pinMode(pin, OUTPUT);
    _isPullup = 1;
    digitalWrite(_pin, HIGH);
}

/// @brief Initialize LED pin with pull-up state
/// @param pin    IO PIN
/// @param pullup Set to 1 if pulled up
LED::LED(uint8_t pin, bool pullup){
    _pin = pin;
    pinMode(pin, OUTPUT);
    if(pullup) { _isPullup = 1;
        digitalWrite(_pin, HIGH);
    } else { _isPullup = 0;
        digitalWrite(_pin, LOW);
    }
}
/// @brief 
void LED::on(){
    if(_isPullup) { digitalWrite(_pin, LOW);
    } else {digitalWrite(_pin, HIGH);}
}
/// @brief 
void LED::off(){
    if(_isPullup) { digitalWrite(_pin, HIGH);
    } else { digitalWrite(_pin, LOW);}
}
/// @brief 
/// @param val 0~0xFF value 
void LED::pwm(uint8_t val){
    if(_isPullup) { analogWrite(_pin, 0xFF-val);
    } else { analogWrite(_pin, val);}
}
/// @brief 
/// @param val 1: On, 0: Off
void LED::set(uint8_t val) {
    if(val) this->on();
    else this->off();
}

/// @brief 
/// @param r 
/// @param g 
/// @param b 
void RGB_LED::set_rgb(uint8_t r, uint8_t g, uint8_t b) {
    this->pLedR->pwm(r);
    this->pLedG->pwm(g);
    this->pLedB->pwm(b);
}

/// @brief 
void RGB_LED::update() {

}