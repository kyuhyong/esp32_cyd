#include "gui_slider.h"

void GUI_SLIDER::config(GUI_SLIDER::Config config, TFT_eSPI* tft) {
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
    
    if(_config.type == GUI_SLIDER::TYPE_V) {
        this->_m_x = _config.width * MARGIN_X;
        this->_m_y = _config.height * MARGIN_Y * 2;
        this->_l_tick = _config.width * LENGTH_TICK;
        this->_t_tick = _config.height * THICKNESS_TICK;
    } else {
        this->_m_x = _config.width * MARGIN_X;
        this->_m_y = _config.height * MARGIN_Y;
        this->_l_tick = _config.height * LENGTH_TICK;
        this->_t_tick = _config.width * THICKNESS_TICK;
    }
    
    this->draw(0.0);
}

void GUI_SLIDER::draw(double value) {
    _disp.createSprite(_config.width, _config.height);
    TFT_eSprite txtSp = TFT_eSprite(_tft);
    txtSp.createSprite(_config.width, _config.height);
    txtSp.fillSprite(TFT_TRANSPARENT);
    txtSp.setTextColor(_config.color_text, TFT_TRANSPARENT, true);
    _disp.fillSprite(_config.color_back);
    _disp.setTextColor(_config.color_text, TFT_TRANSPARENT, true);
    switch (_config.type)
    {
    case GUI_SLIDER::TYPE_V: {
        _disp.setTextDatum(ML_DATUM);
        txtSp.setTextDatum(ML_DATUM);
        // Draw edge
        _disp.drawRect(1, 1,
                    _config.width - 2, _config.height - 2, 
                    _config.color_edge);
        // Draw minor tick
        float tick_step = (float)_config.tick_minor * (_config.height - (float)_m_y*2.0f) / _d_total;
        if(_tick_minor_num > 0) {
            for(int i = 0; i < this->_tick_minor_num ; i++) {
                float ax = _config.width/2;
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
                float ax = _config.width/2;
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
        // Draw slider
        int slider_total = _config.height - _m_y*2;
        int slider_y = _config.height-_m_y - slider_total * _value / _d_total;
        _disp.drawWideLine(_config.width/2, _m_y, 
                            _config.width/2, _config.height - _m_y, 2, 
                            _config.color_bar, _config.color_back);
        _disp.fillCircle(_config.width/2, slider_y, 
                            _config.slider_r, _config.color_slider);        

        _disp.setSwapBytes(false);      //Fix color endian
        txtSp.pushToSprite(&_disp, 0, 0, TFT_TRANSPARENT);
        String txt = String((int)_value);
        _disp.drawString(txt, _config.width/2 , _config.height - _m_y/2, 2);  
        }
        break;
    case GUI_SLIDER::TYPE_H:{
        _disp.setTextDatum(BC_DATUM);
        txtSp.setTextDatum(MC_DATUM);
        // Draw edge
        _disp.drawRect(_m_x-1, _m_y-1,
                    _config.width - _m_x*2 + 1, _config.height - _m_y*2 + 1, 
                    _config.color_edge);
        
        // Draw minor tick
        float tick_step = (float)_config.tick_minor * (_config.width - (float)_m_x*2.0f) / _d_total;
        if(_tick_minor_num > 0) {
            for(int i = 0; i < this->_tick_minor_num ; i++) {
                float ax = _m_x + tick_step*i;
                float ay = _config.height/2;
                _disp.drawWideLine( ax, ay, 
                                    ax, ay + _l_tick, 
                                    _t_tick, _config.color_minor_tick, _config.color_back);
            }
        }
        // Draw major tick
        tick_step = (float)_config.tick_major * (_config.width - (float)_m_x*2.0f) / _d_total;
        if(_tick_major_num > 0) {
            for(int i = 0; i <= _tick_major_num ; i++) {
                float ax = _m_x + tick_step * i;
                float ay = _config.height/2;
                _disp.drawWideLine(ax, ay, 
                    ax, ay  + _l_tick * 2, 
                    _t_tick*2, _config.color_major_tick, _config.color_back);
                String txt = String(i * _config.tick_major);
                double tx = (double)ax;
                double ty = _m_y + _l_tick*3;
                txtSp.drawString(txt, tx, ty, 2);
            }
        }
        // Draw slider
        int slider_x = (_config.width - _m_x*2) * _value / _d_total;
        
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

void GUI_SLIDER::refresh() {
    this->draw(this->_value);
}

void GUI_SLIDER::touch(int t_x, int t_y) {
    // Boundary check first
    if(t_x > _config.pos_x && t_x < _config.pos_x + _config.width) {
        if(t_y > _config.pos_y && t_y < _config.pos_y + _config.height) {
            switch (_config.type)
            {
            case GUI_SLIDER::TYPE_V:
            {
                int dy = _config.pos_y + _config.height - t_y;
                _value = dy * (_config.max - _config.min) / _config.height;
                this->draw(_value);
            }
            break;
            case GUI_SLIDER::TYPE_H:
            {
                int dx = _config.pos_x + _config.width - t_x;
                _value = dx * (_config.max - _config.min) / _config.width;
                this->draw(_value);
                
            }
            break;
            default:
                break;
            }
            if(_cbSliderEvent) {
                _cbSliderEvent(_value);
            }
        }
    }
}