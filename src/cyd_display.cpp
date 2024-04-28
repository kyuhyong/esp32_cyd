#include "cyd_display.h"

static int x, y, z;
static uint16_t _update_interval_ms;
static uint32_t _next_update_ms;

void CYD_DISPLAY::begin(uint16_t interval_ms)
{
    // Start the SPI for the touchscreen and init the touchscreen
    touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
    touchscreen.begin(touchscreenSPI);
    // Set the Touchscreen rotation in landscape mode
    // Note: in some displays, the touchscreen might be upside down, so you might need to set the rotation to 3: touchscreen.setRotation(3);
    touchscreen.setRotation(1);

    // Start the tft display
    tft.init();
    //tft.invertDisplay(1);
    // Set the TFT display rotation in landscape mode
    tft.setRotation(1);

    // Clear the screen before writing to it
    tft.fillScreen(TFT_BLACK);
    
    // Set X and Y coordinates for center of display
    int centerX = SCREEN_WIDTH / 2;
    int centerY = SCREEN_HEIGHT / 2;

    // Set update interval in ms
    _update_interval_ms = interval_ms;
    _next_update_ms = millis() + _update_interval_ms;
    //tft.drawCentreString("Hello, world!", centerX, 30, FONT_SIZE);
    //tft.drawCentreString("Touch screen to test", centerX, centerY, FONT_SIZE);
}

void CYD_DISPLAY::loop()
{
    if(millis() > _next_update_ms) {
        this->refresh();
        _next_update_ms = millis() + _update_interval_ms;
    }
    if (touchscreen.tirqTouched() && touchscreen.touched()) {
        // Get Touchscreen points
        TS_Point p = touchscreen.getPoint();
        // Calibrate Touchscreen points with map function to the correct width and height
        x = map(p.x, 200, 3700, 1, SCREEN_WIDTH);
        y = map(p.y, 240, 3800, 1, SCREEN_HEIGHT);
        z = p.z;
    }
}

// Print Touchscreen info about X, Y and Pressure (Z) on the TFT Display
void CYD_DISPLAY::refresh(void) {
    disp.createSprite(220, 220);
    disp.setSwapBytes(true);
    disp.setTextDatum(ML_DATUM);
    // Update disp
    disp.fillSprite(BACK_COLOR);
    disp.setTextColor(TFT_WHITE, BACK_COLOR);
    
    int textX = 10;
    int textY = 10;

    String tempText = "X = " + String(x);
    disp.drawString(tempText, textX, textY, FONT_SIZE);

    textY += 15;
    tempText = "Y = " + String(y);
    disp.drawString(tempText, textX, textY, FONT_SIZE);

    textY += 15;
    tempText = "Pressure = " + String(z);
    disp.drawString(tempText, textX, textY, FONT_SIZE);

    int arc_deg = map(y, 0, 240, 45, 315);
    disp.drawArc(80, 140, 60, 30, 45, arc_deg, TFT_YELLOW, BACK_COLOR);
    disp.pushSprite(0,0);
    disp.deleteSprite();
}