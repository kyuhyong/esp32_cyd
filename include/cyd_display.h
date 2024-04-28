#ifndef _CYD_DISPLAY_H_
#define _CYD_DISPLAY_H_
#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include "XPT2046_Touchscreen.h"
// Touchscreen pins
#define XPT2046_IRQ 36   // T_IRQ
#define XPT2046_MOSI 32  // T_DIN
#define XPT2046_MISO 39  // T_OUT
#define XPT2046_CLK 25   // T_CLK
#define XPT2046_CS 33    // T_CS

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define FONT_SIZE 2

/**
 * 
*/
class CYD_DISPLAY
{
public:
    CYD_DISPLAY() {};
    ~CYD_DISPLAY(){};
    void begin(void);
    void loop(void);
    TFT_eSPI tft = TFT_eSPI();
    SPIClass touchscreenSPI = SPIClass(VSPI);
    XPT2046_Touchscreen touchscreen = XPT2046_Touchscreen(XPT2046_CS, XPT2046_IRQ);
private:
    void printTouchToDisplay(int touchX, int touchY, int touchZ);

};

extern CYD_DISPLAY display;
#endif