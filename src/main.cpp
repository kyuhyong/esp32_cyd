#include <Arduino.h>
#include "cyd_ldr.h"
#include "cyd_display.h"
#include "RGB_LED.h"
#include "I2C_INMP441.h"
#include "gui_speedometer.h"
#include "gui_bar.h"
#include "gui_textbox.h"
#include "gui_slider.h"
#include "gui_button.h"

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
GUI_SPEEDOMETER::Config config_speed;
GUI_BAR bar1;
GUI_BAR::Config config_bar1;
GUI_BAR bar2;
GUI_BAR::Config config_bar2;
GUI_TEXTBOX tb1;
GUI_TEXTBOX::Config config_tb1;
GUI_SLIDER slider1;
GUI_SLIDER::Config config_slider1;
GUI_BUTTON button1;
GUI_BUTTON::Config config_button1;

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
  slider1.touch(x, y);
  button1.touch(x, y);
  //slider1.set(config_slider1.max - map(y, 0, 240, config_slider1.min, config_slider1.max));
  //slider1.refresh();
  //speedometer.refresh();
}

void handle_sliderEvent(int val) {
  Serial.print("Slider:");
  Serial.println(val);
}

void handle_button1Event(GUI_BUTTON::TOGGLE_STATE state) {
  Serial.print("Button1 : ");
  Serial.println(state);
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
  config_speed.pos_x =    0;
  config_speed.pos_y =    0;
  config_speed.inner_r =  15;
  config_speed.radius =   70;
  config_speed.angle_min = 30;
  config_speed.angle_max = 275;
  config_speed.tick_minor = 10;
  config_speed.tick_major = 20;
  config_speed.font_size =  2;
  config_speed.txt_x = 100;
  config_speed.txt_y = 100;
  config_speed.color_arc =        TFT_YELLOW;
  config_speed.color_minor_tick = COLOR_MINOR_TICK;
  config_speed.color_major_tick = COLOR_MAJOR_TICK;
  config_speed.color_back =       COLOR_BACK;
  config_speed.color_needle =     0xF811;
  speedometer.set(50);
  speedometer.config(config_speed, display.Tft());
  speedometer.unit("Km/h");

  config_bar1.type = GUI_BAR::BAR_TYPE_V;
  config_bar1.min = 0.0;
  config_bar1.max = 100.0;
  config_bar1.width = 40;
  config_bar1.height = 150;
  config_bar1.pos_x = 155;
  config_bar1.pos_y = 0;
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

  config_slider1.type = GUI_SLIDER::TYPE_V;
  config_slider1.min = 0.0;
  config_slider1.max = 100.0;
  config_slider1.width = 40;
  config_slider1.height = 150;
  config_slider1.slider_r = 10;
  config_slider1.pos_x = 200;
  config_slider1.pos_y = 0;
  config_slider1.tick_minor = 5;
  config_slider1.tick_major = 25;
  config_slider1.font = 2;
  config_slider1.color_major_tick = COLOR_MAJOR_TICK;
  config_slider1.color_minor_tick = COLOR_MINOR_TICK;
  config_slider1.color_edge = TFT_LIGHTGREY;
  config_slider1.color_bar = TFT_LIGHTGREY;
  config_slider1.color_slider = TFT_YELLOW;
  config_slider1.color_back = COLOR_BACK;
  config_slider1.color_text = TFT_WHITE;
  slider1.set(50);
  slider1.config(config_slider1, display.Tft());
  slider1.onNewSliderEvent(handle_sliderEvent);
  slider1.refresh();

  config_button1.pos_x = 245;
  config_button1.pos_y = 5;
  config_button1.width = 70;
  config_button1.height = 40;
  config_button1.font = 2;
  config_button1.color_back = COLOR_BACK;
  config_button1.color_button_pressed = TFT_ORANGE;
  config_button1.color_button_release = TFT_DARKGREY;
  config_button1.color_edge = TFT_BLUE;
  config_button1.color_text = TFT_BLACK;
  button1.config(config_button1, display.Tft());
  button1.set_label("LIGHT");
  button1.onNewButtonEvent(handle_button1Event);
  button1.refresh();

  config_bar2.type = GUI_BAR::BAR_TYPE_H;
  config_bar2.min = 0.0;
  config_bar2.max = 100.0;
  config_bar2.width = 150;
  config_bar2.height = 35;
  config_bar2.pos_x = 0;
  config_bar2.pos_y = 160;
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

  config_tb1.width = 160;
  config_tb1.height = 65;
  config_tb1.pos_x = 155;
  config_tb1.pos_y = 155;
  config_tb1.color_back = COLOR_BACK;
  config_tb1.color_edge = TFT_WHITE;
  config_tb1.color_box =  TFT_DARKGREEN;
  config_tb1.color_text = TFT_GREEN;
  config_tb1.datum = ML_DATUM;
  config_tb1.font = 7;    //Digit
  tb1.config(config_tb1, display.Tft());
  tb1.setText("1234");
  tb1.refresh();

  

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
    int num = millis()%10000;
    tb1.setText(String(num));
    tb1.refresh();
    next_update_t = millis()+50;
  }
}

