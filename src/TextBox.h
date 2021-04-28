#pragma once

class TextBox : public Control {
public:
    TextBox(TouchScreen* screen, Window* parent, uint16_t x, uint16_t y, uint16_t width, 
        uint16_t height, uint16_t id = 0);

    String _title{""};
    bool _frame{};
    bool _dropDown{};
    uint16_t _textColor = ILI9341_WHITE;
    int _textSize = 2;

    void update(String text);
    void draw() override;
    bool onTouch(const Point& point) override;
};
