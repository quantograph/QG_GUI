class Window;
class TouchScreen;

class Control {
public:
    // Control types
    enum Type {
        none,
        button,
        edit, // Edit box
        list // List of strings
    };

    Control(TouchScreen* screen, Window* parent, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t id = 0);

    virtual ~Control() {}

    TouchScreen* _screen{};
    Window* _parent{}; // Parent window of this control
    uint16_t _x{0}; // X coordinate of the control upper left corner
    uint16_t _y{0}; // Y coordinate of the control upper left corner
    uint16_t _width{0}; // Control width
    uint16_t _height{0}; // Control height
    String _text{""}; // Control text
    Type _type{Type::none}; // Control type
    uint16_t _id{0}; // Control ID
    bool _hidden{}; // Whether to draw this control

    virtual void draw() {}
    virtual bool onTouch(const Point& point) { return false; }
    virtual bool onRelease(const Point& fromPoint, const Point& toPoint) { return false; }
    virtual bool onMove(const Point& fromPoint, const Point& toPoint) { return false; }
    bool inside(const Point& point);
};
