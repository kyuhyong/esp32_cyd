#include "gui_textbox.h"

void GUI_TEXTBOX::config(GUI_TEXTBOX::Config config, TFT_eSPI* tft) {
    this->_config = config;
    this->_tft = tft;
    this->_disp = TFT_eSprite(tft);
    this->_m_x = config.width * MARGIN_X;
    this->_m_y = config.height * MARGIN_Y;
    this->_font = config.font;
}


void GUI_TEXTBOX::draw(String txt, uint8_t font) {
    _disp.createSprite(_config.width, _config.height);
    _disp.setSwapBytes(true);
    _disp.fillSprite(_config.color_back);
    _disp.setTextColor(_config.color_text, TFT_TRANSPARENT, true);
    _disp.setTextDatum(_config.datum);
    TFT_eSprite txtSp = TFT_eSprite(_tft);
    txtSp.createSprite(_config.width-_m_x*2-2, _config.height-_m_y*2-2);
    txtSp.fillSprite(TFT_TRANSPARENT);
    txtSp.setTextColor(_config.color_text, TFT_TRANSPARENT, false);
    txtSp.setTextDatum(_config.datum);
    // Draw edge
    _disp.fillRect(1, 1, 
                _config.width - 1, _config.height -1, _config.color_edge);

    // Draw box area
    _disp.fillRect(_m_x, _m_y, 
                _config.width - _m_x*2 -1, _config.height - _m_y*2 -1, _config.color_box);
    // Draw text
    txtSp.drawString(txt, _m_x, _config.height/2, font);

    // Push sprite
    _disp.setSwapBytes(false);      //Fix color endian
    txtSp.pushToSprite(&_disp, _m_x, _m_y, TFT_TRANSPARENT);
    _disp.setSwapBytes(true);
    _disp.pushSprite(_config.pos_x, _config.pos_y);
    _disp.deleteSprite();
}

void GUI_TEXTBOX::refresh() {
    this->draw(this->_text, this->_font);
}