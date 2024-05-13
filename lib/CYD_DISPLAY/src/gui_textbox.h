#ifndef _GUI_TEXTBOX_H_
#define _GUI_TEXTBOX_H_

#include <Arduino.h>
#include <TFT_eSPI.h>


class GUI_TEXTBOX{
public:
    
    typedef struct {
        int     width;      // Total Width of sprite
        int     height;     // Total height of sprite
        int     pos_x;      // X Position relative from top left
        int     pos_y;      // Y position relative from top left
        uint8_t     datum;              // String alignment
        uint8_t     font;               // Font
        uint16_t    color_back;         // Color for background
        uint16_t    color_box;          // Color for box area
        uint16_t    color_text;         // Color for text
        uint16_t    color_edge;         // Color for edge
    }Config;
    GUI_TEXTBOX(){};
    ~GUI_TEXTBOX(){};

    void config(GUI_TEXTBOX::Config config, TFT_eSPI* tft);
    /// @brief Set value
    void setText(String text){ _text = text; };
    void setFont(uint8_t font) { _font = font; };
    void refresh();

private:
    TFT_eSPI* _tft;
    TFT_eSprite _disp = TFT_eSprite(_tft);
    GUI_TEXTBOX::Config _config;
    String _text;
    uint8_t _font;
    int _m_x;      //Left margin
    int _m_y;
    static constexpr float MARGIN_X = 0.05;    //5% margin L
    static constexpr float MARGIN_Y = 0.05;     //Top margin
    void draw(String txt, uint8_t font);
};

#endif