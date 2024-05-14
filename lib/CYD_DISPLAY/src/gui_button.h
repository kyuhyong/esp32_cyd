#ifndef _GUI_BUTTON_H_
#define _GUI_BUTTON_H_

#include <Arduino.h>
#include <TFT_eSPI.h>


class GUI_BUTTON{
public:
    
    typedef enum {
        BOX = 0,
        CIRCLE
    }BUTTON_TYPE;

    typedef enum {
        TOGGLE_NONE = 0,
        TOGGLE_PRESSED,
        TOGGLE_RELEASED
    }TOGGLE_STATE;

    typedef void (*ButtonEvent)(TOGGLE_STATE);

    typedef struct {
        int     width;      // Total Width of sprite
        int     height;     // Total height of sprite
        int     pos_x;      // X Position relative from top left
        int     pos_y;      // Y position relative from top left
        BUTTON_TYPE     button_type;   // Bar type
        uint8_t     font;
        uint16_t    color_back;         // Color for background
        uint16_t    color_button_release; // Color for button normal
        uint16_t    color_button_pressed; // Color for button pressed
        uint16_t    color_text;         // Color for any text
        uint16_t    color_edge;         // Color for edge
    }Config;
    GUI_BUTTON(){};
    ~GUI_BUTTON(){};

    void config(GUI_BUTTON::Config config, TFT_eSPI* tft);
    /// @brief Set value
    void set_state(TOGGLE_STATE state){ _state = state; };
    void set_label(String label){ _label = label; };
    void touch(int x, int y);
    void refresh();
    void onNewButtonEvent(ButtonEvent event) { _cbButtonEvent = event; }

private:
    TFT_eSPI* _tft;
    TFT_eSprite _disp = TFT_eSprite(_tft);
    GUI_BUTTON::Config _config;
    ButtonEvent _cbButtonEvent;
    TOGGLE_STATE _state;
    int _m_x;       // margin x
    int _m_y;       // margin y
    int _round_r;
    String _label;
    bool _is_button_ready;
    static constexpr float MARGIN_X = 0.1;     //5% margin L
    static constexpr float MARGIN_Y = 0.1;     //5% Top margin
    static constexpr float ROUND_R = 0.1;       // 10% round R
    void draw(TOGGLE_STATE);
};

#endif