#include "RGB_LED.h"

/// @brief Initialize LED pin default pull-up state
/// @param pin IO PIN
LED::LED(uint8_t pin){
    _pin = pin;
    this->_current_state = LED_STATE_NORMAL;
    pinMode(pin, OUTPUT);
    _isPullup = 1;
    digitalWrite(_pin, HIGH);
}

/// @brief Initialize LED pin with pull-up state
/// @param pin    IO PIN
/// @param pullup Set to 1 if pulled up
LED::LED(uint8_t pin, bool pullup){
    _pin = pin;
    this->_current_state = LED_STATE_NORMAL;
    pinMode(pin, OUTPUT);
    if(pullup) { _isPullup = 1;
        digitalWrite(_pin, HIGH);
    } else { _isPullup = 0;
        digitalWrite(_pin, LOW);
    }
}
/// @brief 
void LED::on(){
    this->_isOn= true;
    if(_isPullup) { digitalWrite(_pin, LOW);
    } else {digitalWrite(_pin, HIGH);}
}
/// @brief 
void LED::off(){
    this->_isOn = false;
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

/// @brief Start blink for every set off time then on time
/// @param off_time_ms 
/// @param on_time_ms 
void LED::blink(uint16_t off_time_ms, uint16_t on_time_ms) {
    this->_current_state = LED_STATE_BLINK;
    this->_off_ms = off_time_ms;
    this->_on_ms = on_time_ms;
    this->_next_ms = millis() + off_time_ms;
    this->off();
}

void LED::update() {
    switch(this->_current_state) {
        case LED_STATE_NORMAL:{

        }
        break;
        case LED_STATE_BLINK:{
            if(millis() > this->_next_ms) {
                if(!this->_isOn) {
                    this->on();
                    this->_next_ms = millis()+ this->_on_ms;
                } else {
                    this->off();
                    this->_next_ms = millis() + this->_off_ms;
                }
            }
        }
        break;
        case LED_STATE_STROBE:{

        }
        break;
    }
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
    this->pLedR->update();
    this->pLedG->update();
    this->pLedB->update();
}