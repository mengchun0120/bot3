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

rapidjson::Value MouseButtonEvent::toJson(
                rapidjson::Document::AllocatorType& allocator) const
{
    using namespace rapidjson;

    Value v(kObjectType);

    v.AddMember("x", x_, allocator);
    v.AddMember("y", y_, allocator);
    v.AddMember("button", jsonVal(buttonStr(button_), allocator), allocator);
    v.AddMember("action", jsonVal(actionStr(action_), allocator), allocator);
    v.AddMember("mods", mods_, allocator);

    return v;
}

void MouseMoveEvent::set(float x,
                         float y)
{
    x_ = x;
    y_ = y;
}

rapidjson::Value MouseMoveEvent::toJson(
                rapidjson::Document::AllocatorType& allocator) const
{
    using namespace rapidjson;

    Value v(kObjectType);

    v.AddMember("x", x_, allocator);
    v.AddMember("y", y_, allocator);

    return v;
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

rapidjson::Value KeyEvent::toJson(
                rapidjson::Document::AllocatorType& allocator) const
{
    using namespace rapidjson;

    Value v(kObjectType);

    v.AddMember("key", key_, allocator);
    v.AddMember("action", jsonVal(actionStr(action_), allocator), allocator);
    v.AddMember("scancode", scancode_, allocator);
    v.AddMember("mods", mods_, allocator);

    return v;
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

InputEvent& InputEvent::operator=(const InputEvent& e)
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

const MouseButtonEvent& InputEvent::mouseButtonEvent() const
{
    if (type_ != EventType::MOUSE_BUTTON)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Event is not a mouse-button event");
    }

    return mouseButtonEvent_;
}

const MouseMoveEvent& InputEvent::mouseMoveEvent() const
{
    if (type_ != EventType::MOUSE_MOVE)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Event is not a mouse-move event");
    }

    return mouseMoveEvent_;
}

const KeyEvent& InputEvent::keyEvent() const
{
    if (type_ != EventType::KEY)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Event is not key event");
    }

    return keyEvent_;
}

rapidjson::Value InputEvent::toJson(
                rapidjson::Document::AllocatorType& allocator) const
{
    using namespace rapidjson;

    Value v(kObjectType);

    v.AddMember("class", "InputEvent", allocator);
    v.AddMember("type", jsonVal(stringVal(type_), allocator), allocator);

    Value evt;
    switch (type_)
    {
        case EventType::MOUSE_BUTTON:
            evt = mouseButtonEvent_.toJson(allocator);
            break;
        case EventType::MOUSE_MOVE:
            evt = mouseMoveEvent_.toJson(allocator);
            break;
        case EventType::KEY:
            evt = keyEvent_.toJson(allocator);
            break;
    }

    v.AddMember("event", evt, allocator);
    v.AddMember("base", Object::toJson(allocator), allocator);

    return v;
}

#endif

} // end of namespace commonlib
} // end of namespace mcdane

