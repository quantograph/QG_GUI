#include <QG_Devices.h>
#include <QG_Include.h>
#include "Control.h"
//#include "Button.h"
#include "Window.h"
#include "List.h"

//=================================================================================================
List::List() {

}

//=================================================================================================
bool List::init(TouchScreen* screen, Window* parent, uint16_t id) {
    Window::init(screen, parent, id);

    // Get the list size
    _listWidth = _screen->_width - 2;
    _itemHeight = _screen->_height / _itemsToShow;
    _listHeight = _itemHeight * _itemsToShow - 1;

    return true;
}

//=================================================================================================
void List::activate() {
    //Serial.printf("List::activate\n");
    _ready = false;
    _lastScroll = -1;
    Window::activate();
}

//=================================================================================================
// Get the current scroll
int16_t List::getScroll() {
    int16_t scroll = _scroll + _moveScroll;

    if(scroll < 0)
        scroll = 0;

    uint16_t max = _items.size() - _itemsToShow;
    if(scroll > max)
        scroll = max;

    //Serial.printf("List::getScroll: _scroll=%d, _moveScroll=%d, scroll=%d, _items.size()=%d, _itemsToShow=%d, max=%d\n", _scroll, _moveScroll, scroll, _items.size(), _itemsToShow, max);
 
    return scroll;
}

//=================================================================================================
void List::draw() {
    uint16_t scroll = getScroll();
    ///Serial.printf("List::draw: scroll=%d\n", scroll);
    if(scroll == _lastScroll) {
        //Serial.printf("scroll=%d, _lastScroll=%d\n", scroll, _lastScroll);
        return;
    }

    _lastScroll = scroll;
    Window::draw();

    _screen->_screen->setTextColor(_textColor);
    _screen->_screen->setTextSize(_textSize);
    uint16_t y = 2;

    for(uint16_t index = scroll; index < _items.size(); ++index) {
        _screen->_screen->setCursor(10, y + 17);
        _screen->_screen->print(_items[index].first);
        //Serial.printf("Item: %s\n", _items[index].first.c_str());
        
        y += _itemHeight;
        if(y > _listHeight)
            break;

        _screen->_screen->drawFastHLine(0, y, _listWidth, ILI9341_NAVY);
    }

    _screen->_screen->drawRect(1, 1, _listWidth, _listHeight, ILI9341_NAVY);
}

//=================================================================================================
bool List::onTouch(const Point& point) {
    if(!_ready) {
        //Serial.printf("List::onTouch: NOT READY\n");
        return false;
    }

    Window::onTouch(point);

    //Serial.printf("List::onTouch\n");
    _touchPoint = point;

    return true;
}

//=================================================================================================
bool List::onRelease(const Point& fromPoint, const Point& toPoint) {
    if(_ready) {
        //Serial.printf("List::onRelease: ready\n");
        checkRelease(fromPoint, toPoint);
    } else {
        //Serial.printf("List::onRelease: NOT READY\n");
    }

    _ready = true;
    return true;
}

//=================================================================================================
bool List::onMove(const Point& fromPoint, const Point& toPoint) {
    if(!_ready)
        return false;

    _moveScroll = (_touchPoint._y - toPoint._y) / _itemHeight;
    //Serial.printf("List::onMove, Scroll: (%3d-%3d)%3d / %3d = %3d\n", _touchPoint._y, toPoint._y, _touchPoint._y - toPoint._y, _itemHeight, _moveScroll);
    draw();

    return true;
}

//=================================================================================================
void List::checkRelease(const Point& fromPoint, const Point& toPoint) {
    //Serial.printf("List::checkRelease\n");

    _scroll = getScroll();
    _lastScroll = _scroll;

    uint16_t move = abs(fromPoint._y - toPoint._y);
    if(move < _itemHeight) {
        int16_t index = _scroll + toPoint._y / _itemHeight;
        index = std::max(index, (int16_t)0);
        index = std::min(index, (int16_t)(_items.size() - 1));
        _selectedString = _items[index].first;
        _selectedId = (uint16_t)_items[index].second;
        //Serial.printf("List::onRelease, selected: %s (%d)\n", _selectedString.c_str(), _selectedId);
        _parent->onBack(this);
    }
}
