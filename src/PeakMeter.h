#pragma once

class TouchScreen;

class PeakMeter : public Control {
public:
    PeakMeter(TouchScreen* screen, Window* parent, uint16_t x, uint16_t y, uint16_t width, 
                uint16_t height, uint16_t id = 0);
    
    void draw() override;
    void update(float left, float right);
    void drawMeterBar(uint16_t y, uint16_t height, float value);
};
