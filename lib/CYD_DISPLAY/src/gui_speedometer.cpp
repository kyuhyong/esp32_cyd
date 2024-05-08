#include "gui_speedometer.h"

void GUI_SPEEDOMETER::config(Speedometer_Config config, TFT_eSPI* tft) {
    this->_config = config;
    this->_tft = tft;
    this->_disp = TFT_eSprite(tft);
    _d_total = (int)(_config.max - _config.min);
    _tick_minor_num = _d_total / _config.tick_minor;
    _tick_major_num = _d_total / _config.tick_major;
    this->draw();
}

void GUI_SPEEDOMETER::draw(void) {
    _disp.createSprite(_config.width, _config.height);
    _disp.setSwapBytes(true);
    _disp.setTextDatum(MC_DATUM);
    // Update disp
    _disp.fillSprite(_config.color_back);
    _disp.setTextColor(TFT_WHITE, _config.color_back);
    
    int arc_x = _config.width/2;
    int arc_y = _config.height/2;

    // Draw arc edge
    _disp.drawSmoothArc(arc_x, arc_y, _config.radius , _config.radius - 2, 
                    _config.angle_min, _config.angle_max, _config.color_major_tick, _config.color_back);

    _disp.drawSmoothArc(arc_x, arc_y, _config.radius - 5 , _config.radius - 7, 
                    _config.angle_min, _config.angle_max, _config.color_minor_tick, _config.color_back);
    // Draw minor tick
    int d_angle = _config.angle_max - _config.angle_min;
    int tick_angle_step = _config.tick_minor * d_angle / _d_total;
    for(int i = 0 ; i < _tick_minor_num; i++) {
        _disp.drawSmoothArc(arc_x, arc_y, _config.radius - 8, _config.radius - 13, 
                _config.angle_min+i*tick_angle_step - 1, _config.angle_min+i*tick_angle_step + 1, _config.color_minor_tick, _config.color_back);
    }
    // Draw major tick
    tick_angle_step = _config.tick_major * d_angle / _d_total;
    for(int i = 0 ; i <= _tick_major_num; i++) {
        double tick_angle = _config.angle_min + i * tick_angle_step;
        _disp.drawSmoothArc(arc_x, arc_y, _config.radius - 8, _config.radius - 15, 
                tick_angle - 2, tick_angle + 2, _config.color_major_tick, _config.color_back);
        double tick_rad = tick_angle * DEG_TO_RAD;
        double t_x = arc_x - (_config.radius - 28) * sin(tick_rad);
        double t_y = arc_y + (_config.radius - 28) * cos(tick_rad);
        String txt = String(i*_config.tick_major);
        _disp.drawString(txt, t_x, t_y, 2);
    }
    // Draw needle and bar
    // First convert value to angle
    int arc_deg = map(_value, _config.min, _config.max, _config.angle_min, _config.angle_max);
    // Draw bar
    _disp.drawSmoothArc(arc_x , arc_y, _config.radius - 35, _config.inner_r, 
                    _config.angle_min, arc_deg, _config.color_arc, _config.color_back);
    // Then Draw needle
    double arc_rad = (double)arc_deg * DEG_TO_RAD;
    double ndl_x1 = arc_x - (_config.radius - 20) * sin(arc_rad);
    double ndl_y1 = arc_y + (_config.radius - 20)* cos(arc_rad);
    _disp.drawWedgeLine(ndl_x1, ndl_y1, arc_x, arc_y, 2, 4, _config.color_needle, _config.color_back);
    _disp.drawSmoothArc(arc_x, arc_y,_config.inner_r+2, _config.inner_r, 
        _config.angle_min, _config.angle_max, _config.color_major_tick, _config.color_back);
    _disp.fillSmoothCircle(arc_x, arc_y, _config.inner_r, _config.color_back);
    
    String tempText = String((int)_value);
    _disp.drawString(tempText, 
        arc_x, arc_y, _config.font_size);

    _disp.pushSprite(_config.pos_x, _config.pos_y);
    _disp.deleteSprite();
}

void GUI_SPEEDOMETER::refresh() {
    this->draw();
}