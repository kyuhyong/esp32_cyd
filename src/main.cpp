#include <Arduino.h>
#include "cyd_ldr.h"
#include "cyd_display.h"
#include "RGB_LED.h"
#include "I2C_INMP441.h"
#include "gui_speedometer.h"

#define CYD_LED_BLUE    17
#define CYD_LED_GREEN   16
#define CYD_LED_RED     4

#define I2S_WS_PIN    7
#define I2S_SD_PIN    33
#define I2S_SCK_PIN   36

LDR ldr;
CYD_DISPLAY display;
GUI_SPEEDOMETER speedometer;
GUI_SPEEDOMETER::Speedometer_Config config_speed;
RGB_LED rgb(CYD_LED_RED, CYD_LED_GREEN, CYD_LED_BLUE);
//INMP441 mic(I2S_WS_PIN, I2S_SD_PIN, I2S_SCK_PIN, -1);
INMP441 mic;
int32_t mic_samples[DMA_BUFFER_SIZE];

uint32_t next_update_t = 100;
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
  config_speed.min =      0.0;
  config_speed.max =      200.0;
  config_speed.width =    150;
  config_speed.height =   150;
  config_speed.pos_x =    50;
  config_speed.pos_y =    50;
  config_speed.inner_r =  40;
  config_speed.radius =   60;
  config_speed.angle_min = 30;
  config_speed.angle_max = 275;
  config_speed.tick_minor = 5;
  config_speed.tick_major = 10;
  config_speed.font_size =  4;
  config_speed.color_arc = TFT_WHITE;
  config_speed.color_back = 0x0026;
  speedometer.config(config_speed, display.Tft());

  rgb.pLedR->off();
  rgb.pLedG->off();
  rgb.pLedB->off();
  rgb.pLedR->blink(800, 200);
  if(mic.init() == 0) {
    Serial.println("INMP441 init OK!");
  } else {
    Serial.println("INMP441 init FAIL!");
  }
}

void loop() {
  display.loop();
  rgb.update();
  // size_t bytes_read = 0;
  // i2s_read(I2S_NUM_0, mic_samples, sizeof(int32_t) * DMA_BUFFER_SIZE, &bytes_read, portMAX_DELAY);
  // int samples_read = bytes_read / sizeof(int32_t);
  // if(samples_read > 0) {
  //   for (int i = 0; i<samples_read; i++) {
  //     Serial.print(mic_samples[i]);
  //     Serial.print(",");
  //   }
  //   Serial.println();
  // }
  // int samples = mic.read(mic_samples, DMA_BUFFER_SIZE);
  // if(samples > 0) {
  //   for (int i = 0; i<samples; i++) {
  //     Serial.print(mic_samples[i]);
  //     Serial.print(",");
  //   }
  //   Serial.println();
  // }
  if(millis() > next_update_t) {
    // Serial.print("LDR:");
    // Serial.print(ldr.get());
    // Serial.println();
    next_update_t = millis()+10;
  }
}

