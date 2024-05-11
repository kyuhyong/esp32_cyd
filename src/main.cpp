#include <Arduino.h>
#include "cyd_ldr.h"
#include "cyd_display.h"
#include "RGB_LED.h"
#include "I2C_INMP441.h"
#include "gui_speedometer.h"
#include "gui_bar.h"

#define CYD_LED_BLUE    17
#define CYD_LED_GREEN   16
#define CYD_LED_RED     4

#define I2S_WS_PIN    7
#define I2S_SD_PIN    33
#define I2S_SCK_PIN   36

#define COLOR_BACK        0x0026        //Dark blue
#define COLOR_MAJOR_TICK  0x055D        //Light Blue
#define COLOR_MINOR_TICK  TFT_LIGHTGREY
#define COLOR_NEEDLE      0xF811        //Red

LDR ldr;
CYD_DISPLAY display;
GUI_SPEEDOMETER speedometer;
GUI_SPEEDOMETER::Speedometer_Config config_speed;
GUI_BAR bar1;
GUI_BAR::Bar_Config config_bar1;
GUI_BAR bar2;
GUI_BAR::Bar_Config config_bar2;

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
  speedometer.set(config_speed.max - map(y, 0, 240, config_speed.min, config_speed.max));
  bar1.set(config_bar1.max - map(y, 0, 240, config_bar1.min, config_bar1.max));
  bar1.refresh();
  bar2.set(map(x, 0, 320, config_bar2.min, config_bar2.max));
  bar2.refresh();
  //speedometer.refresh();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  ldr.begin();
  display.begin(50);
  display.onNewTouchEvent(handle_touchEvent);
  config_speed.min =      0.0;
  config_speed.max =      200.0;
  config_speed.width =    190;
  config_speed.height =   190;
  config_speed.pos_x =    0;
  config_speed.pos_y =    0;
  config_speed.inner_r =  40;
  config_speed.radius =   90;
  config_speed.angle_min = 30;
  config_speed.angle_max = 275;
  config_speed.tick_minor = 10;
  config_speed.tick_major = 20;
  config_speed.font_size =  4;
  config_speed.color_arc =        TFT_YELLOW;
  config_speed.color_minor_tick = COLOR_MINOR_TICK;
  config_speed.color_major_tick = COLOR_MAJOR_TICK;
  config_speed.color_back =       COLOR_BACK;
  config_speed.color_needle =     0xF811;
  speedometer.set(50);
  speedometer.config(config_speed, display.Tft());

  config_bar1.type = GUI_BAR::BAR_TYPE_V;
  config_bar1.min = 0.0;
  config_bar1.max = 100.0;
  config_bar1.width = 40;
  config_bar1.height = 150;
  config_bar1.pos_x = 210;
  config_bar1.pos_y = 40;
  config_bar1.tick_minor = 5;
  config_bar1.tick_major = 25;
  config_bar1.color_major_tick = COLOR_MAJOR_TICK;
  config_bar1.color_minor_tick = COLOR_MINOR_TICK;
  config_bar1.color_edge = TFT_LIGHTGREY;
  config_bar1.color_text = TFT_WHITE;
  config_bar1.color_bar = TFT_CYAN;
  config_bar1.color_back = COLOR_BACK;
  config_bar1.font_size = 2;
  bar1.set(50);
  bar1.config(config_bar1, display.Tft());
  bar1.refresh();

  config_bar2.type = GUI_BAR::BAR_TYPE_H;
  config_bar2.min = 0.0;
  config_bar2.max = 100.0;
  config_bar2.width = 150;
  config_bar2.height = 40;
  config_bar2.pos_x = 10;
  config_bar2.pos_y = 195;
  config_bar2.tick_minor = 5;
  config_bar2.tick_major = 25;
  config_bar2.color_major_tick = COLOR_MAJOR_TICK;
  config_bar2.color_minor_tick = COLOR_MINOR_TICK;
  config_bar2.color_edge = TFT_LIGHTGREY;
  config_bar2.color_text = TFT_WHITE;
  config_bar2.color_bar = TFT_PURPLE;
  config_bar2.color_back = COLOR_BACK;
  config_bar2.font_size = 2;
  bar2.set(50);
  bar2.config(config_bar2, display.Tft());
  bar2.refresh();

  

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
  speedometer.loop();
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
    next_update_t = millis()+10;
  }
}

