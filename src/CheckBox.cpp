#include <QG_Devices.h>
#include <QG_Include.h>
#include "Window.h"
#include "Control.h"
#include "CheckBox.h"

//=================================================================================================
CheckBox::CheckBox(TouchScreen* screen, Window* parent, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t id) : 
    Control(screen, parent, x, y, width, height, id) {
}

//=================================================================================================
void CheckBox::update(bool checked) {
    _checked = checked;
    draw();
}

//=================================================================================================
void CheckBox::draw() {
    _screen->_screen->fillRect(_x, _y, _width, _height, ILI9341_BLACK);

    // Check box
    _screen->_screen->fillRect(_x, _y, _height, _height, _checked ? ILI9341_BLUE : ILI9341_BLACK);
    _screen->_screen->drawRect(_x, _y, _height, _height, ILI9341_WHITE);

    // Text
    _screen->_screen->setCursor(_x + _height + 5, _y + 7);
    _screen->_screen->setTextColor(_textColor);
    _screen->_screen->setTextSize(_textSize);
    _screen->_screen->print(_text);
}

//=================================================================================================
bool CheckBox::onTouch(const Point& point) {
    if(!inside(point)) {
        //Serial.printf("CheckBox::onTouch, not inside: %s, touch=%dx%d, box=%dx%d,%dx%d\n", _text.c_str(), point.x, point.y, _x, _y, _x + _width, _y + _height);
        return false;
    }

    //Serial.printf("CheckBox::onTouch, inside: %s %dx%d\n", _text.c_str(), point.x, point.y);
    _parent->onControl(this);

    return true;
}
