#ifndef INCLUDED_COMMONLIB_INPUT_EVENT_H
#define INCLUDED_COMMONLIB_INPUT_EVENT_H

#include <string>
#include <ostream>
#include <commonlib_opengl.h>

namespace mcdane {
namespace commonlib {

#ifdef DESKTOP_APP

std::string buttonStr(int button);

std::string actionStr(int action);

struct MouseButtonEvent {
    void set(float x,
             float y,
             int button,
             int action,
             int mods);

    float x_;
    float y_;
    int button_;
    int action_;
    int mods_;
};

struct MouseMoveEvent {
    void set(float x,
             float y);

    float x_;
    float y_;
};

struct KeyEvent {
    void set(int key,
             int action,
             int scancode,
             int mods);

    int key_;
    int action_;
    int scancode_;
    int mods_;
};

class InputEvent {
public:
    enum EventType {
        ET_MOUSE_BUTTON,
        ET_MOUSE_MOVE,
        ET_KEY,
        ET_UNKNOWN
    };

    InputEvent();

    ~InputEvent() = default;

    EventType type() const
    {
        return type_;
    }

    InputEvent& operator=(const InputEvent& e);

    void setMouseButtonEvent(float x,
                             float y,
                             int button,
                             int action,
                             int mods);

    void setMouseMoveEvent(float x,
                           float y);

    void setKeyEvent(int key,
                     int action,
                     int scancode,
                     int mods);

    const MouseButtonEvent& mouseButtonEvent() const;

    const MouseMoveEvent& mouseMoveEvent() const;

    const KeyEvent& keyEvent() const;

private:
    EventType type_;
    union {
        MouseButtonEvent mouseButtonEvent_;
        MouseMoveEvent mouseMoveEvent_;
        KeyEvent keyEvent_;
    };
};

#endif // #ifdef DESTTOP_APP

} // end of namespace commonlib
} // end of namespace mcdane

namespace std {

#ifdef DESKTOP_APP
std::ostream& operator<<(std::ostream& os,
                         const mcdane::commonlib::MouseButtonEvent& e);

std::ostream& operator<<(std::ostream& os,
                         const mcdane::commonlib::MouseMoveEvent& e);

std::ostream& operator<<(std::ostream& os,
                         const mcdane::commonlib::KeyEvent& e);

std::ostream& operator<<(std::ostream& os,
                         const mcdane::commonlib::InputEvent& e);
#endif

} // end of namespace std

#endif // #ifndef INCLUDED_COMMONLIB_INPUT_EVENT_H

