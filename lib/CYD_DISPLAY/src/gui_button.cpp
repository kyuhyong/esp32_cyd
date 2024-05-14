#include "gui_button.h"


void GUI_BUTTON::config(GUI_BUTTON::Config config, TFT_eSPI* tft) {
    this->_config = config;
    this->_tft = tft;
    this->_disp = TFT_eSprite(tft);
    this->_state = TOGGLE_STATE::TOGGLE_NONE;
    this->_m_x = _config.width * MARGIN_X;
    this->_m_y = _config.height * MARGIN_Y;
    this->_round_r = _config.height * ROUND_R;
    this->_is_button_ready = true;
    this->draw(_state);
}

void GUI_BUTTON::draw(TOGGLE_STATE state) {
    _disp.createSprite(_config.width, _config.height);
    TFT_eSprite txtSp = TFT_eSprite(_tft);
    txtSp.createSprite(_config.width, _config.height);
    txtSp.fillSprite(TFT_TRANSPARENT);
    txtSp.setTextColor(_config.color_text, TFT_TRANSPARENT, true);
    _disp.fillSprite(_config.color_back);
    _disp.setTextColor(_config.color_text, TFT_TRANSPARENT, true);
    
    _disp.fillRoundRect(0, 0, 
            _config.width, _config.height, 
            _round_r, _config.color_edge);
    if(state == TOGGLE_STATE::TOGGLE_NONE || state == TOGGLE_STATE::TOGGLE_RELEASED) {
        _disp.fillRoundRect(_m_x, _m_y, 
                _config.width - _m_x*2, _config.height - _m_y*2, 
                _round_r, _config.color_button_release);
    } else {
        _disp.fillRoundRect(_m_x, _m_y, 
                _config.width - _m_x*2, _config.height - _m_y*2, 
                _round_r, _config.color_button_pressed);
    }
    txtSp.setTextDatum(MC_DATUM);
    txtSp.drawString(_label, _config.width/2, _config.height/2, _config.font);
    _disp.setSwapBytes(false);
    txtSp.pushToSprite(&_disp, 0, 0, TFT_TRANSPARENT);
    _disp.setSwapBytes(true);
    _disp.pushSprite(_config.pos_x, _config.pos_y);
    _disp.deleteSprite();
}

void GUI_BUTTON::refresh() {
    this->draw(this->_state);
}

void GUI_BUTTON::touch(int t_x, int t_y) {
    // Boundary check first
    if(t_x > _config.pos_x && t_x < _config.pos_x + _config.width) {
        if(t_y > _config.pos_y && t_y < _config.pos_y + _config.height) {
            if(_is_button_ready) {
                // Toggle is not pressed
                if(_state == TOGGLE_NONE || _state == TOGGLE_RELEASED) {
                    if(_state!=TOGGLE_PRESSED) {
                        _state = TOGGLE_PRESSED;
                        this->draw(_state);
                        if(_cbButtonEvent) {
                            _cbButtonEvent(_state);
                        }
                    }
                } else {
                    // Toggle is already in pressed state
                    if(_state == TOGGLE_PRESSED) {
                        _state = TOGGLE_RELEASED;
                        this->draw(_state);
                        if(_cbButtonEvent) {
                            _cbButtonEvent(_state);
                        }
                    }
                }
                _is_button_ready = false;
                return;
            }
            
        }
    }
    // when button is not in ready
    if(!_is_button_ready) {
        _is_button_ready = true;
    }
}