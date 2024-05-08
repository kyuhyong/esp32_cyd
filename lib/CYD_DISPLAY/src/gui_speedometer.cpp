#include "gui_speedometer.h"

void GUI_SPEEDOMETER::config(Speedometer_Config config, TFT_eSPI* tft) {
    this->_config = config;
    this->_tft = tft;
    this->_disp = TFT_eSprite(tft);
    _tick_total = (int)(_config.max - _config.min);
    _tick_minor_num = _tick_total / _config.tick_minor;
    _tick_major_num = _tick_total / _config.tick_major;
    this->draw();
}

void GUI_SPEEDOMETER::draw(void) {
    _disp.createSprite(_config.width, _config.height);
    _disp.setSwapBytes(true);
    _disp.setTextDatum(ML_DATUM);
    // Update disp
    _disp.fillSprite(_config.color_back);
    _disp.setTextColor(TFT_WHITE, _config.color_back);
    
    
    int arc_deg = map(_value, _config.min, _config.max, _config.angle_min, _config.angle_max);
    int arc_x = _config.width/2;
    int arc_y = _config.height/2;
    _disp.drawArc(arc_x, arc_y, _config.radius+3, _config.radius, 
                    _config.angle_min, _config.angle_max, TFT_WHITE, _config.color_back);
    
    int tick_step = _tick_total / _config.tick_minor;

    for(int i = 0 ; i < _tick_minor_num; i++) {
        _disp.drawArc(arc_x, arc_y, _config.radius+3, _config.radius, 
                _config.angle_min+i*)
    }
    _disp.drawArc(arc_x , arc_y, _config.radius, _config.inner_r, 
                    _config.angle_min, arc_deg, _config.color_arc, _config.color_back);
    String tempText = String(_value);
    _disp.drawString(tempText, 
        _config.width/2, 
        _config.height - 10, _config.font_size);

    _disp.pushSprite(_config.pos_x, _config.pos_y);
    _disp.deleteSprite();
}