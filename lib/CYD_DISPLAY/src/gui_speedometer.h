#ifndef _GUI_SPEEDOMETER_H_
#define _GUI_SPEEDOMETER_H_

#include <Arduino.h>
#include <TFT_eSPI.h>

class GUI_SPEEDOMETER{
public:
    typedef enum {
        SPEEDOMETER_ARC_BAR = 0,
        SPEEDOMETER_ARROW
    }SPEEDOMETER_TYPE;

    typedef struct {
        double min;
        double max;
        int     tick_minor;
        int     tick_major;
        int     width;
        int     height;
        int     pos_x;
        int     pos_y;
        int     radius;
        int     inner_r;
        int     angle_min;
        int     angle_max;
        uint8_t     font_size;
        uint16_t    color_back;
        uint16_t    color_arc;
        SPEEDOMETER_TYPE type;
    }Speedometer_Config;
    GUI_SPEEDOMETER(){};
    ~GUI_SPEEDOMETER(){};

    void config(Speedometer_Config config, TFT_eSPI* tft);
    void set(double value){ _value = value; };
    void refresh();

private:
    TFT_eSPI* _tft;
    TFT_eSprite _disp = TFT_eSprite(_tft);
    Speedometer_Config _config;
    double _value;
    int _tick_minor_num;
    int _tick_major_num;
    int _tick_total;
    void draw(void);
};

#endif