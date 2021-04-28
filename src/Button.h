#pragma once

class TouchScreen;

class Button : public Control {
public:
    Button(TouchScreen* screen, Window* parent,  uint16_t x, uint16_t y, uint16_t width, 
            uint16_t height, String text, uint16_t id = 0);

    int _radius = 7; // Radius of the rectangle rounding
    uint16_t _backColor = ILI9341_NAVY; // Button's background color
    uint16_t _borderColor = ILI9341_WHITE; // Button's border color
    uint16_t _textColor = ILI9341_WHITE; // Button's text color
    int _textSize = 2; // Text size
    char _string[32];

    void draw() override;
    bool onTouch(const Point& point) override;
    bool onRelease(const Point& fromPoint, const Point& toPoint) override;
};
