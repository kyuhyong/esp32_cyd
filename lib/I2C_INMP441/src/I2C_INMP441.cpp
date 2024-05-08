#include "I2C_INMP441.h"

int INMP441::init() {
    i2s_driver_config_t i2s_config = {};
    i2s_config.mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX);
    i2s_config.sample_rate =        I2S_SAMPLE_RATE;
    i2s_config.bits_per_sample =    I2S_BITS_PER_SAMPLE_32BIT;
    i2s_config.channel_format =     I2S_CHANNEL_FMT_ONLY_LEFT;
    i2s_config.communication_format = I2S_COMM_FORMAT_I2S;
        // i2s_comm_format_t(I2S_COMM_FORMAT_STAND_I2S |
        //                   I2S_COMM_FORMAT_I2S_MSB);
    i2s_config.intr_alloc_flags =   ESP_INTR_FLAG_LEVEL1;
    i2s_config.dma_buf_count =      DMA_BUFFER_COUNT;
    i2s_config.dma_buf_len =        DMA_BUFFER_LEN;
    i2s_config.use_apll =           false;
    i2s_config.tx_desc_auto_clear = false;
    i2s_config.fixed_mclk =         0;

    auto result = i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
    if (result != ESP_OK) {
        return -1;
    }

    result = i2s_set_pin(I2S_NUM_0, &this->_pin_config);
    if (result != ESP_OK) {
        return -1;
    }
    return 0;
}

// reads the microphone data into data.
// int INMP441::read(std::array<int16_t, INMP441::BUFFERDEPTH>& data) {
//     size_t bytesRead = 0;
//     esp_err_t result_I2S0 = i2s_read(I2S_NUM_0, &data, sizeof(int16_t) * BUFFERDEPTH,
//                                      &bytesRead, TICKS_TO_WAIT);
//     if (result_I2S0 != ESP_OK || bytesRead != BUFFERDEPTH) {
//         return -1;
//     }
//     return 0;
// }
int INMP441::read(int32_t *data, uint16_t size) {
    size_t bytesRead = 0;
    esp_err_t result_I2S0 = i2s_read(I2S_NUM_0, data, sizeof(int32_t) * size,
                                     &bytesRead, TICKS_TO_WAIT);
    if (result_I2S0 != ESP_OK || bytesRead != BUFFERDEPTH) {
        return -1;
    }
    int samples_read = bytesRead / sizeof(int32_t);
    return samples_read;
}