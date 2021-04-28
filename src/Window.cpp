#include <QG_Devices.h>
#include <QG_Include.h>
#include "Control.h"
#include "Window.h"

//=================================================================================================
Window::Window() {
}

//=================================================================================================
Window::~Window() {
    for(auto control : _controls){
        delete control;
    }
}

//=================================================================================================
bool Window::init(TouchScreen* screen, Window* parent, uint16_t id) {
    _screen = screen;
    _parent = parent;
    _id = id;

    return true;
}

//=================================================================================================
void Window::draw() {
    _screen->_screen->fillScreen(ILI9341_BLACK);

    for(auto control : _controls){
        if(!control->_hidden)
            control->draw();
    }
}

//=================================================================================================
bool Window::onTouch(const Point& point) {
    for(auto control : _controls)
        control->onTouch(point);

    return false;
}

//=================================================================================================
bool Window::onRelease(const Point& fromPoint, const Point& toPoint) {
    for(auto control : _controls)
        control->onRelease(fromPoint, toPoint);

    return false;
}

//=================================================================================================
bool Window::onMove(const Point& fromPoint, const Point& toPoint) {
    for(auto control : _controls)
        control->onMove(fromPoint, toPoint);

    return false;
}
