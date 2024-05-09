#include "gui_bar.h"

void GUI_BAR::config(Bar_Config config, TFT_eSPI* tft) {
    this->_config = config;
    this->_tft = tft;
    this->_disp = TFT_eSprite(tft);
    _d_total = (int)(_config.max - _config.min);
    if(_config.tick_minor > 0) {
        _tick_minor_num = _d_total / _config.tick_minor;
    } else { 
        _tick_minor_num = 0;
    }
    if(_config.tick_major > 0) {
        _tick_major_num = _d_total / _config.tick_major;
    } else {
        _tick_major_num = 0;
    }
    
    this->draw(0.0);
}

void GUI_BAR::draw(double value) {

}