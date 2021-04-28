#include <QG_Devices.h>
#include <QG_Include.h>
#include "Window.h"
#include "Control.h"
#include "Button.h"

//=================================================================================================
Button::Button(TouchScreen* screen, Window* parent, uint16_t x, uint16_t y, uint16_t width, 
                uint16_t height, String text, uint16_t id) : 
    Control(screen, parent, x, y, width, height, id) {
    _text = text;
}

//=================================================================================================
void Button::draw() {
    // Draw the button's frame
	_screen->_screen->fillRoundRect(_x, _y, _width, _height, _radius, _backColor);
	_screen->_screen->drawRoundRect(_x, _y, _width, _height, _radius, _borderColor);

    // Draw the text
    _screen->_screen->setCursor(_x + 5, _y + 20);
    _screen->_screen->setTextColor(_textColor);
    _screen->_screen->setTextSize(_textSize);
    _screen->_screen->print(_text);
}

//=================================================================================================
bool Button::onTouch(const Point& point) {
    if(!inside(point))
        return false;

    //Serial.printf("Button::onTouch: %s\n", _text.c_str());
    _parent->onControl(this);

    return true;
}

//=================================================================================================
bool Button::onRelease(const Point& fromPoint, const Point& toPoint) {

    return false;
}
