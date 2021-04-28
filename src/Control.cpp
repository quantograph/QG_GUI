#include <QG_Devices.h>
#include "Window.h"
#include "Control.h"

//=================================================================================================
Control::Control(TouchScreen* screen, Window* parent, uint16_t x, uint16_t y, uint16_t width, 
                    uint16_t height, uint16_t id) : 
    _screen(screen), _parent(parent), _x(x), _y(y), _width(width), _height(height), _id(id) {
    //Serial.printf("=====> Adding control: %p\n", this);

    if(_parent)
        _parent->_controls.push_back(this);
}

//=================================================================================================
// Whether the point is inside the control
bool Control::inside(const Point& point) {
    if(point._x >= _x && point._x <= _x + _width &&
       point._y >= _y && point._y <= _y + _height)
        return true;
    else
        return false;
}
