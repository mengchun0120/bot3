#include <commonlib_exception.h>
#include <commonlib_input_event.h>

namespace mcdane {
namespace commonlib {

#ifdef DESKTOP_APP

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

