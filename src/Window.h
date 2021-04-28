#pragma once

class Control;
class TouchScreen;

class Window {
public:
    Window();
    virtual ~Window();

    TouchScreen* _screen{};
    Window* _parent{};
    std::list<Control*> _controls{};
    uint16_t _id{0};

    virtual void draw();
    virtual void activate() {};
    virtual bool init(TouchScreen* screen, Window* parent, uint16_t id = 0);
    virtual bool onTouch(const Point& point);
    virtual bool onRelease(const Point& fromPoint, const Point& toPoint);
    virtual bool onMove(const Point& fromPoint, const Point& toPoint);
    virtual void onPeakMeter(float left, float right) {}
    virtual bool onControl(Control* control) { return false; }
    virtual void onBack(Window* window) {}
};
