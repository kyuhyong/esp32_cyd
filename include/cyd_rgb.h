#ifndef _CYD_RGB_H_
#define _CYD_RGB_H_

#include <Arduino.h>

#define CYD_LED_BLUE    17
#define CYD_LED_GREEN   16
#define CYD_LED_RED     4

#define CYD_LED_ON      LOW
#define CYD_LED_OFF     HIGH

class CYD_RGBLED
{
public:
    CYD_RGBLED(){};
    ~CYD_RGBLED(){};
   // --------------------------------------- 
	void begin(void)
    {
        pinMode(CYD_LED_RED, OUTPUT);
        digitalWrite(CYD_LED_RED, CYD_LED_OFF);
        pinMode(CYD_LED_GREEN, OUTPUT);
        pinMode(CYD_LED_BLUE, OUTPUT);
        digitalWrite(CYD_LED_GREEN, CYD_LED_OFF);
        digitalWrite(CYD_LED_BLUE, CYD_LED_OFF);      
    }
	
    void set(uint8_t r, uint8_t g, uint8_t b){
        analogWrite(CYD_LED_RED, 0xFF-r);
        analogWrite(CYD_LED_BLUE, 0xFF-g);
        analogWrite(CYD_LED_GREEN, 0xFF-b);
    }
private:

};

extern CYD_RGBLED rgb;

#endif