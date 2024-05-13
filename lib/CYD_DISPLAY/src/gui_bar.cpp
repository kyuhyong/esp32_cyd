#include "gui_bar.h"

void GUI_BAR::config(GUI_BAR::Config config, TFT_eSPI* tft) {
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
    
    if(_config.type == BAR_TYPE_V) {
        this->_m_x_left = _config.width * MARGIN_X_L;
        this->_m_x_right = _config.width * MARGIN_X_R;
        this->_m_y = _config.height * MARGIN_Y * 2;
        this->_l_tick = _config.width * LENGTH_TICK;
        this->_t_tick = _config.height * THICKNESS_TICK;
    } else {
        this->_m_x_left = _config.width * MARGIN_X_R;       //Same margin for left and right
        this->_m_x_right = _config.width * MARGIN_X_R;
        this->_m_y = _config.height * MARGIN_Y;
        this->_l_tick = _config.height * LENGTH_TICK;
        this->_t_tick = _config.width * THICKNESS_TICK;
    }
    
    this->draw(0.0);
}

void GUI_BAR::draw(double value) {
    _disp.createSprite(_config.width, _config.height);
    TFT_eSprite txtSp = TFT_eSprite(_tft);
    txtSp.createSprite(_config.width, _config.height);
    txtSp.fillSprite(TFT_TRANSPARENT);
    txtSp.setTextColor(_config.color_text, TFT_TRANSPARENT, true);
    _disp.fillSprite(_config.color_back);
    _disp.setTextColor(_config.color_text, TFT_TRANSPARENT, true);
    switch (_config.type)
    {
    case BAR_TYPE_V: {
        _disp.setTextDatum(ML_DATUM);
        txtSp.setTextDatum(ML_DATUM);
        // Draw edge
        _disp.drawRect(_m_x_left-1, _m_y-1,
                    _config.width - _m_x_left - _m_x_right + 1, _config.height - _m_y*2 + 1, 
                    _config.color_edge);
        // Draw bar
        int bar_y = (_config.height - _m_y*2) * _value / _d_total;
        _disp.fillRect( _m_x_left + _l_tick, _config.height - _m_y - bar_y, 
                    _config.width - _m_x_left - _m_x_right - _l_tick-2 , bar_y,
                    _config.color_bar);
        // Draw minor tick
        float tick_step = (float)_config.tick_minor * (_config.height - (float)_m_y*2.0f) / _d_total;
        if(_tick_minor_num > 0) {
            for(int i = 0; i < this->_tick_minor_num ; i++) {
                float ax = _m_x_left;
                float ay = _config.height - _m_y - tick_step*i;
                _disp.drawWideLine( ax, ay, 
                                    ax + _l_tick, ay, 
                                    _t_tick, _config.color_minor_tick, _config.color_back);
            }
        }
        // Draw major tick
        tick_step = (float)_config.tick_major * (_config.height - (float)_m_y*2.0f) / _d_total;
        if(_tick_major_num > 0) {
            for(int i = 0; i <= _tick_major_num ; i++) {
                float ax = _m_x_left;
                float ay = _config.height - _m_y - tick_step*i;
                _disp.drawWideLine(ax, ay, 
                    ax + _l_tick * 2, ay, 
                    _t_tick*2, _config.color_major_tick, _config.color_back);
                String txt = String(i * _config.tick_major);
                double tx = 1;
                double ty = (double)ay;
                txtSp.drawString(txt, tx, ty, 2);
            }
        }
        _disp.setSwapBytes(false);      //Fix color endian
        txtSp.pushToSprite(&_disp, 0, 0, TFT_TRANSPARENT);
        String txt = String((int)_value);
        _disp.drawString(txt, _config.width/2 , _config.height - _m_y/2, 2);  
        }
        break;
    case BAR_TYPE_H:{
        _disp.setTextDatum(BC_DATUM);
        txtSp.setTextDatum(MC_DATUM);
        // Draw edge
        _disp.drawRect(_m_x_left-1, _m_y-1,
                    _config.width - _m_x_left*2 + 1, _config.height - _m_y*2 + 1, 
                    _config.color_edge);
        // Draw bar
        int bar_x = (_config.width - _m_x_left*2) * _value / _d_total;
        _disp.fillRect( _m_x_left + 1, _m_y + _l_tick, 
                    bar_x , _config.height - _m_y*2 - _l_tick*3,
                    _config.color_bar);
        // Draw minor tick
        float tick_step = (float)_config.tick_minor * (_config.width - (float)_m_x_left*2.0f) / _d_total;
        if(_tick_minor_num > 0) {
            for(int i = 0; i < this->_tick_minor_num ; i++) {
                float ax = _m_x_left + tick_step*i;
                float ay = _m_y;
                _disp.drawWideLine( ax, ay, 
                                    ax, ay + _l_tick, 
                                    _t_tick, _config.color_minor_tick, _config.color_back);
            }
        }
        // Draw major tick
        tick_step = (float)_config.tick_major * (_config.width - (float)_m_x_left*2.0f) / _d_total;
        if(_tick_major_num > 0) {
            for(int i = 0; i <= _tick_major_num ; i++) {
                float ax = _m_x_left + tick_step * i;
                float ay = _m_y;
                _disp.drawWideLine(ax, ay, 
                    ax, ay  + _l_tick * 2, 
                    _t_tick*2, _config.color_major_tick, _config.color_back);
                String txt = String(i * _config.tick_major);
                double tx = (double)ax;
                double ty = _m_y + _l_tick*3;
                txtSp.drawString(txt, tx, ty, 2);
            }
        }
        _disp.setSwapBytes(false);      //Fix color endian
        txtSp.pushToSprite(&_disp, 0, 0, TFT_TRANSPARENT);
        String txt = String((int)_value);
        _disp.drawString(txt, _config.width/2 , _config.height - _m_y/2, 2);  
        }   
        break;
    default:
        break;
    }
    _disp.setSwapBytes(true);
    _disp.pushSprite(_config.pos_x, _config.pos_y);
    _disp.deleteSprite();
}

void GUI_BAR::refresh() {
    this->draw(this->_value);
}