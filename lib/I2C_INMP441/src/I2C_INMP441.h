#ifndef _I2C_INMP441_H_
#define _I2C_INMP441_H_

#include <Arduino.h>

#define I2S_SAMPLE_RATE 8000
#define DMA_BUFFER_SIZE 512
#define DMA_BUFFER_COUNT 4
#define DMA_BUFFER_LEN  1024

class INMP441 {
private:

    //static constexpr uint32_t   DMA_BUFFER_LEN = 1024;
    static constexpr uint32_t   TICKS_TO_WAIT = 1000;
    static constexpr int8_t     NOT_USED = -1;
    static constexpr uint8_t    I2S_WS_I2S0 = 25;
    static constexpr uint8_t    I2S_SD_I2S0 = 33;
    static constexpr uint8_t    I2S_SCK_I2S0 = 26;
public:
    // defines the buffer size.
    static constexpr uint16_t BUFFERDEPTH = 8000;
    // sample_rate / bufferdepth = loops per seconds
    // -> 8000/512 = 15,25 ~ 16 -> for 1 seconds of recordings, 16 loops are nessesary
    static constexpr uint16_t counter = (I2S_SAMPLE_RATE / BUFFERDEPTH) + 1;
    int     init();
    int     read(std::array<int16_t, INMP441::BUFFERDEPTH> &data);

};

#endif