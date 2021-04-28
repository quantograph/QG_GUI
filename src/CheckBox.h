#pragma once

class CheckBox : public Control {
public:
    CheckBox(TouchScreen* screen, Window* parent, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t id = 0);

    bool _checked{};
    uint16_t _textColor = ILI9341_WHITE;
    int _textSize = 2;

    void update(bool checked);
    void draw() override;
    bool onTouch(const Point& point) override;
};
