#include <QG_Devices.h>
#include <QG_Include.h>
#include "Window.h"
#include "Control.h"
#include "TextBox.h"

//=================================================================================================
TextBox::TextBox(TouchScreen* screen, Window* parent, uint16_t x, uint16_t y, uint16_t width, 
                 uint16_t height, uint16_t id) : 
    Control(screen, parent, x, y, width, height, id) {
}

//=================================================================================================
void TextBox::update(String text) {
    _text = text;
    draw();
}

//=================================================================================================
void TextBox::draw() {
    _screen->_screen->fillRect(_x, _y, _width, _height, ILI9341_BLACK);
    _screen->_screen->setCursor(_x + 7, _y + 7);
    _screen->_screen->setTextColor(_textColor);
    _screen->_screen->setTextSize(_textSize);
    _screen->_screen->print(_text);

    if(_frame)
        _screen->_screen->drawRect(_x, _y, _width, _height, ILI9341_WHITE);

    if(_dropDown) {
        _screen->_screen->drawRect(_x + _width, _y, _height, _height, ILI9341_WHITE);

        int16_t x = _x + _width + 5;
        int16_t y = _y + 8;
        int16_t width = _height - 10;
        _screen->_screen->fillTriangle(x, y, x + width, y, x + width * 0.5, 
                                                 y + width * 0.55, ILI9341_WHITE);
    }
}

//=================================================================================================
bool TextBox::onTouch(const Point& point) {
    if(!inside(point))
        return false;

    _parent->onControl(this);

    return true;
}
