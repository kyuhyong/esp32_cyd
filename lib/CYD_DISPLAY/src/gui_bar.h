#ifndef _GUI_BAR_H_
#define _GUI_BAR_H_

#include <Arduino.h>
#include <TFT_eSPI.h>


class GUI_BAR{
public:
    typedef enum {
        BAR_TYPE_V = 0,
        BAR_TYPE_H
    }BAR_TYPE;
    typedef struct {
        double min;         // Minimum value
        double max;         // Maximum value
        int     tick_minor; // Minor tick value
        int     tick_major; // Major tick value
        int     width;      // Total Width of sprite
        int     height;     // Total height of sprite
        int     pos_x;      // X Position relative from top left
        int     pos_y;      // Y position relative from top left
        BAR_TYPE    type;   // Bar type
        uint8_t     font_size;
        uint16_t    color_back;         // Color for background
        uint16_t    color_bar;          // Color for bar
        uint16_t    color_minor_tick;   // Color for minor ticks
        uint16_t    color_major_tick;   // Color for major ticks, edge of control
        uint16_t    color_text;         // Color for any text
        uint16_t    color_edge;         // Color for edge
    }Bar_Config;
    GUI_BAR(){};
    ~GUI_BAR(){};

    void config(Bar_Config config, TFT_eSPI* tft);
    /// @brief Set value
    void set(double value){ _value = value; };
    void refresh();

private:
    TFT_eSPI* _tft;
    TFT_eSprite _disp = TFT_eSprite(_tft);
    Bar_Config _config;
    double _value;
    int _tick_minor_num;
    int _tick_major_num;
    int _d_total;
    int _l_tick;
    int _m_x;
    int _m_y;
    float _t_tick;
    static constexpr float MARGIN_X = 0.05;     //5%
    static constexpr float MARGIN_Y = 0.05;
    static constexpr float LENGTH_TICK = 0.1f;
    static constexpr float THICKNESS_TICK = 0.01f;
    void draw(double);
};

#endif