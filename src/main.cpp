#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include "XPT2046_Touchscreen.h"
#include "cyd_ldr.h"
#include "cyd_display.h"
#include "cyd_rgb.h"

LDR ldr;
CYD_DISPLAY display;
CYD_RGBLED rgb;

uint32_t next_update_t = 100;
uint8_t rgb_r = 0;
// put function declarations here:

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  ldr.begin();
  display.begin(50);
  rgb.begin();
}

void loop() {
  display.loop();
  if(millis() > next_update_t) {
    rgb.set(rgb_r, 0, 0);
    if(rgb_r++ > 255) {
      rgb_r = 0;
    }
    Serial.print("LDR:");
    Serial.print(ldr.get());
    Serial.println();
    next_update_t = millis()+10;
  }
}

