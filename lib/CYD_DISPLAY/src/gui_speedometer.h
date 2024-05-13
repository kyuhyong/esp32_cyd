#ifndef _GUI_SPEEDOMETER_H_
#define _GUI_SPEEDOMETER_H_

#include <Arduino.h>
#include <TFT_eSPI.h>

#define PID_KP          0.35
#define PID_KD          0.02
#define PID_KI          0.25
#define LOOP_TIME_MS    30

class GUI_SPEEDOMETER{
public:
    typedef struct {
        double min;         // Minimum value
        double max;         // Maximum value
        int     tick_minor; // Minor tick value
        int     tick_major; // Major tick value
        int     width;      // Total Width of sprite
        int     height;     // Total height of sprite
        int     pos_x;      // X Position relative from top left
        int     pos_y;      // Y position relative from top left
        int     radius;     // Outer most radius (Should not exceed width/2 or height/2 whichever lower)
        int     inner_r;    // Inner circle radius (should not exceed radius / 2)
        int     angle_min;  // Angle for min value
        int     angle_max;  // Angle for max value
        int     txt_x;      // Text X Position
        int     txt_y;      // Text Y Position
        uint8_t     font_size;
        uint16_t    color_back;         // Color for background
        uint16_t    color_arc;          // Color for arc bar
        uint16_t    color_minor_tick;   // Color for minor ticks
        uint16_t    color_major_tick;   // Color for major ticks, edge of control
        uint16_t    color_needle;       // Color for needle
    }Config;
    GUI_SPEEDOMETER(){};
    ~GUI_SPEEDOMETER(){};

    void config(GUI_SPEEDOMETER::Config config, TFT_eSPI* tft);
    /// @brief Set value
    void set(double value){ _value = value; };
    void unit(String unit){ _s_unit = unit; };
    void refresh();
    void loop();

private:
    TFT_eSPI* _tft;
    TFT_eSprite _disp = TFT_eSprite(_tft);
    GUI_SPEEDOMETER::Config _config;
    double _value;
    int _tick_minor_num;
    int _tick_major_num;
    int _d_total;
    double _value_last;     // For loop control
    double _error_i;        // Error accumulation
    double _error_prev;     // For derivative error
    uint32_t _next_millis;
    String  _s_unit;
    static constexpr double ERROR_I_MAX = 1000;
    void draw(double);
};

#endif