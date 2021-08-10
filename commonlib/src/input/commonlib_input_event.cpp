#include <commonlib_exception.h>
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

InputEvent::InputEvent()
    : type_(ET_UNKNOWN)
{
}

InputEvent& InputEvent::operator=(const InputEvent& e)
{
    type_ = e.type_;
    switch (e.type_)
    {
        case ET_MOUSE_BUTTON:
            mouseButtonEvent_ = e.mouseButtonEvent_;
            break;
        case ET_MOUSE_MOVE:
            mouseMoveEvent_ = e.mouseMoveEvent_;
            break;
        case ET_KEY:
            keyEvent_ = e.keyEvent_;
            break;
        default:
            break;
    }

    return *this;
}

void InputEvent::setMouseButtonEvent(float x,
                                     float y,
                                     int button,
                                     int action,
                                     int mods)
{
    type_ = ET_MOUSE_BUTTON;
    mouseButtonEvent_.set(x, y, button, action, mods);
}

void InputEvent::setMouseMoveEvent(float x,
                                   float y)
{
    type_ = ET_MOUSE_MOVE;
    mouseMoveEvent_.set(x, y);
}

void InputEvent::setKeyEvent(int key,
                             int action,
                             int scancode,
                             int mods)
{
    type_ = ET_KEY;
    keyEvent_.set(key, action, scancode, mods);
}

const MouseButtonEvent& InputEvent::mouseButtonEvent() const
{
    if (type_ != ET_MOUSE_BUTTON)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Event is not a mouse-button event");
    }

    return mouseButtonEvent_;
}

const MouseMoveEvent& InputEvent::mouseMoveEvent() const
{
    if (type_ != ET_MOUSE_MOVE)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Event is not a mouse-move event");
    }

    return mouseMoveEvent_;
}

const KeyEvent& InputEvent::keyEvent() const
{
    if (type_ != ET_KEY)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Event is not key event");
    }

    return keyEvent_;
}

#endif

} // end of namespace commonlib
} // end of namespace mcdane

namespace std {

#ifdef DESKTOP_APP
std::ostream& operator<<(std::ostream& os,
                         const mcdane::commonlib::MouseButtonEvent& e)
{
    using namespace mcdane::commonlib;

    os << "MouseButtonEvent(x=" << e.x_
       << ", y=" << e.y_
       << ", button=" << buttonStr(e.button_)
       << ", action=" << actionStr(e.action_)
       << ", mods=" << e.mods_ << ')';
    return os;
}

std::ostream& operator<<(std::ostream& os,
                         const mcdane::commonlib::MouseMoveEvent& e)
{
    os << "MouseMoveEvent(x=" << e.x_
       << ", y=" << e.y_ << ')';
    return os;
}

std::ostream& operator<<(std::ostream& os,
                         const mcdane::commonlib::KeyEvent& e)
{
    using namespace mcdane::commonlib;

    os << "KeyEvent(key=" << e.key_
       << ", action=" << actionStr(e.action_)
       << ", scancode=" << e.scancode_
       << ", mods=" << e.mods_ << ')';
    return os;
}

std::ostream& operator<<(std::ostream& os,
                         const mcdane::commonlib::InputEvent& e)
{
    using namespace mcdane::commonlib;

    switch(e.type())
    {
        case InputEvent::ET_MOUSE_BUTTON:
            return os << e.mouseButtonEvent();
        case InputEvent::ET_MOUSE_MOVE:
            return os << e.mouseMoveEvent();
        case InputEvent::ET_KEY:
            return os << e.keyEvent();
    }
    os << "Unknown Event";
    return os;
}

#endif

} // end of namespace std

