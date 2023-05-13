#include <commonlib_exception.h>
#include <commonlib_string_utils.h>
#include <commonlib_json_utils.h>
#include <commonlib_input_event.h>

namespace mcdane {
namespace commonlib {

#ifdef DESKTOP_APP

std::string buttonStr(int button)
{
    switch(button)
    {
        case GLFW_MOUSE_BUTTON_LEFT:
            return "left";
        case GLFW_MOUSE_BUTTON_RIGHT:
            return "right";
        case GLFW_MOUSE_BUTTON_MIDDLE:
            return "middle";
    }

    return "unknown";
}

std::string actionStr(int action)
{
    switch(action)
    {
        case GLFW_RELEASE:
            return "release";
        case GLFW_PRESS:
            return "press";
    }

    return "unknown";
}

void MouseButtonEvent::set(float x,
                           float y,
                           int button,
                           int action,
                           int mods)
{
    x_ = x;
    y_ = y;
    button_ = button;
    action_ = action;
    mods_ = mods;
}

void MouseMoveEvent::set(float x,
                         float y)
{
    x_ = x;
    y_ = y;
}

void KeyEvent::set(int key,
                   int action,
                   int scancode,
                   int mods)
{
    key_ = key;
    action_ = action;
    scancode_ = scancode;
    mods_ = mods;
}

std::string stringVal(EventType t)
{
    switch(t)
    {
        case EventType::MOUSE_BUTTON:
            return "MOUSE_BUTTON";
        case EventType::MOUSE_MOVE:
            return "MOUSE_MOVE";
        case EventType::KEY:
            return "KEY";
        default:
            THROW_EXCEPT(InvalidArgumentException, "Invalid EventType " +
                         std::to_string(static_cast<int>(t)));

    }
}

InputEvent &InputEvent::operator=(const InputEvent& e)
{
    type_ = e.type_;
    switch (e.type_)
    {
        case EventType::MOUSE_BUTTON:
            mouseButtonEvent_ = e.mouseButtonEvent_;
            break;
        case EventType::MOUSE_MOVE:
            mouseMoveEvent_ = e.mouseMoveEvent_;
            break;
        case EventType::KEY:
            keyEvent_ = e.keyEvent_;
            break;
        default:
            THROW_EXCEPT(InvalidArgumentException, "Invalid EventType " +
                         std::to_string(static_cast<int>(e.type_)));
    }

    return *this;
}

void InputEvent::setMouseButtonEvent(float x,
                                     float y,
                                     int button,
                                     int action,
                                     int mods)
{
    type_ = EventType::MOUSE_BUTTON;
    mouseButtonEvent_.set(x, y, button, action, mods);
}

void InputEvent::setMouseMoveEvent(float x,
                                   float y)
{
    type_ = EventType::MOUSE_MOVE;
    mouseMoveEvent_.set(x, y);
}

void InputEvent::setKeyEvent(int key,
                             int action,
                             int scancode,
                             int mods)
{
    type_ = EventType::KEY;
    keyEvent_.set(key, action, scancode, mods);
}

const MouseButtonEvent &InputEvent::mouseButtonEvent() const
{
    if (type_ != EventType::MOUSE_BUTTON)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Event is not a mouse-button event");
    }

    return mouseButtonEvent_;
}

const MouseMoveEvent &InputEvent::mouseMoveEvent() const
{
    if (type_ != EventType::MOUSE_MOVE)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Event is not a mouse-move event");
    }

    return mouseMoveEvent_;
}

const KeyEvent &InputEvent::keyEvent() const
{
    if (type_ != EventType::KEY)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Event is not key event");
    }

    return keyEvent_;
}

char translateLetter(const KeyEvent &event)
{
    char start;

    if (capsLockEnabled(event))
    {
        start = shiftPressed(event) ? 'a' : 'A';
    }
    else
    {
        start = shiftPressed(event) ? 'A' : 'a';
    }

    return start + (event.key_ - GLFW_KEY_A);
}

char translateDigit(const KeyEvent &event)
{
    static const char shiftChars[] = {
        ')', '!', '@', '#', '$', '%', '^', '&', '*', '('
    };

    int idx = event.key_ - GLFW_KEY_0;

    return shiftPressed(event) ? shiftChars[idx] : '0' + idx;
}

std::pair<int, bool> translateOthers(const KeyEvent &event)
{
    int ch;
    bool printable = true;
    bool shift = shiftPressed(event);

    switch (event.key_)
    {
        case GLFW_KEY_SPACE:
            ch = ' ';
            break;
        case GLFW_KEY_APOSTROPHE:
            ch = shift ? '\"' : '\'';
            break;
        case GLFW_KEY_COMMA:
            ch = shift ? '<' : ',';
            break;
        case GLFW_KEY_MINUS:
            ch = shift ? '_' : '-';
            break;
        case GLFW_KEY_PERIOD:
            ch = shift ? '>' : '.';
            break;
        case GLFW_KEY_SLASH:
            ch = shift ? '?' : '/';
            break;
        case GLFW_KEY_SEMICOLON:
            ch = shift ? ';' : ':';
            break;
        case GLFW_KEY_EQUAL:
            ch = shift ? '+' : '=';
            break;
        case GLFW_KEY_LEFT_BRACKET:
            ch = shift ? '{' : '[';
            break;
        case GLFW_KEY_RIGHT_BRACKET:
            ch = shift ? '}' : ']';
            break;
        case GLFW_KEY_BACKSLASH:
            ch = shift ? '|' : '\\';
            break;
        case GLFW_KEY_GRAVE_ACCENT:
            ch = shift ? '~' : '`';
            break;
        default:
            ch = event.key_;
            printable = false;
            break;
    }

    return std::make_pair(ch, printable);
}

std::pair<int, bool> translate(const KeyEvent &event)
{
    if (event.key_ >= GLFW_KEY_A && event.key_ <= GLFW_KEY_Z)
    {
        return std::make_pair(translateLetter(event), true);
    }
    else if (event.key_ >= GLFW_KEY_0 && event.key_ <= GLFW_KEY_9)
    {
        return std::make_pair(translateDigit(event), true);
    }

    return translateOthers(event);
}

#elif __ANDROID__

std::string toString(InputEvent::Type t)
{
    static std::string str[] = {
        "PointerDown",
        "PointerUp",
        "PointerMove",
    };

    return str[static_cast<int>(t)];
}

#endif

} // end of namespace commonlib
} // end of namespace mcdane

namespace std {

using namespace mcdane::commonlib;

#ifdef DESKTOP_APP
std::ostream & operator<<(std::ostream & os,
                          const MouseButtonEvent &e)
{
    os << "MouseButtonEvent(button=" << buttonStr(e.button_)
       << ", action=" << actionStr(e.action_)
       << ", x=" << e.x_
       << ", y=" << e.y_
       << ", mods=" << e.mods_
       << ")";

    return os;
}

std::ostream & operator<<(std::ostream & os,
                          const MouseMoveEvent &e)
{
    os << "MouseMoveEvent(x=" << e.x_ << ", y=" << e.y_ << ")";
    return os;
}

std::ostream & operator<<(std::ostream & os,
                          const KeyEvent &e)
{
    os << "KeyEvent(action=" << actionStr(e.action_)
       << ", key=" << e.key_
       << ", scanCode=" << e.scancode_
       << ", modes=" << e.mods_
       << ")";

    return os;
}

std::ostream & operator<<(std::ostream & os,
                          const InputEvent &e)
{
    switch (e.type())
    {
        case EventType::MOUSE_BUTTON:
            return os << e.mouseButtonEvent();
        case EventType::MOUSE_MOVE:
            return os << e.mouseMoveEvent();
        case EventType::KEY:
            return os << e.keyEvent();
        default:
            break;
    }

    return os;
}

#elif __ANDROID__

std::ostream & operator<<(std::ostream & os,
                          const InputEvent &e)
{
    os << toString(e.type_) << "(x=" << e.x_
       << ", y=" << e.y_ << ", index=" << e.index_ << ")";

    return os;
}

#endif


} // end of namespace std


