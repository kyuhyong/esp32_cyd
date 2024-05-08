#ifndef _I2C_INMP441_H_
#define _I2C_INMP441_H_

#include <Arduino.h>
#include "driver/i2s.h"

#define I2S_SAMPLE_RATE 8000
#define DMA_BUFFER_SIZE 512
#define DMA_BUFFER_COUNT 4
#define DMA_BUFFER_LEN  1024
#define TICKS_TO_WAIT   1000

#define I2S_SCK         GPIO_NUM_22
#define I2S_WS          GPIO_NUM_12
#define I2S_SDA         GPIO_NUM_33

class INMP441 {
private:
    i2s_pin_config_t    _pin_config;
public:
    INMP441(uint8_t WS_PIN, uint8_t SD_PIN, uint8_t SCK_PIN, uint8_t DOUT_PIN) {
        _pin_config.bck_io_num =    SCK_PIN;
        _pin_config.ws_io_num =     WS_PIN;
        _pin_config.data_out_num =  I2S_PIN_NO_CHANGE;
        _pin_config.data_in_num =   SD_PIN;
    };
    INMP441(){
        _pin_config.bck_io_num =    I2S_SCK;
        _pin_config.ws_io_num =     I2S_WS;
        _pin_config.data_out_num =  I2S_PIN_NO_CHANGE;
        _pin_config.data_in_num =   I2S_SDA;
    };
    ~INMP441(){};
    // defines the buffer size.
    static constexpr uint16_t BUFFERDEPTH = 8000;
    // sample_rate / bufferdepth = loops per seconds
    // -> 8000/512 = 15,25 ~ 16 -> for 1 seconds of recordings, 16 loops are nessesary
    static constexpr uint16_t counter = (I2S_SAMPLE_RATE / BUFFERDEPTH) + 1;
    int     init();
    //int     read(std::array<int16_t, INMP441::BUFFERDEPTH> &data);
    int     read(int32_t *data, uint16_t size);

};

#endif