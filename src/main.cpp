#include <Arduino.h>
#include "cyd_ldr.h"
#include "cyd_display.h"
#include "RGB_LED.h"
#include "I2C_INMP441.h"

#define CYD_LED_BLUE    17
#define CYD_LED_GREEN   16
#define CYD_LED_RED     4

LDR ldr;
CYD_DISPLAY display;
RGB_LED rgb(CYD_LED_RED, CYD_LED_GREEN, CYD_LED_BLUE);
INMP441 mic;

uint32_t next_update_t = 100;
uint8_t rgb_r = 0;
uint8_t rgb_r_state = 0;
// put function declarations here:

void handle_touchEvent(int x, int y, int z) {
  Serial.print("Touched:");
  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  Serial.print(",");
  Serial.print(z);
  Serial.println();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  ldr.begin();
  display.begin(50);
  display.onNewTouchEvent(handle_touchEvent);
  rgb.pLedR->off();
  rgb.pLedG->off();
  mic.init();
  digitalWrite(CYD_LED_GREEN, LOW);
}

void loop() {
  display.loop();
  if(millis() > next_update_t) {
    //rgb.set_rgb(rgb_r, 0, 0);
    if(rgb_r++ > 49) {
      rgb_r_state^=1;
      if(rgb_r_state) {
        rgb.pLedR->on();
        rgb.pLedB->off();
      } else {
        rgb.pLedR->off();
        rgb.pLedB->on();
      }
      rgb_r = 0;
    }
    // Serial.print("LDR:");
    // Serial.print(ldr.get());
    // Serial.println();
    next_update_t = millis()+10;
  }
}

