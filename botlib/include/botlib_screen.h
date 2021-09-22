#ifndef INCLUDED_BOTLIB_SCREEN_H
#define INCLUDED_BOTLIB_SCREEN_H

#include <commonlib_vector.h>
#include <commonlib_input_event.h>

namespace mcdane {
namespace botlib {

class ScreenManager;

class Screen {
public:
    enum Type {
        SCREEN_START,
        SCREEN_GAME,
        SCREEN_SHOW_MAP,
        SCREEN_NONE
    };

    static Screen* create(Type type,
                          const commonlib::Vector2& viewportSize,
                          ScreenManager* screenMgr);

    static bool isValidScreen(Type type)
    {
        return type >= SCREEN_START && type < SCREEN_NONE;
    }

    Screen() = default;

    virtual ~Screen() = default;

    virtual void update() = 0;

    virtual void present() = 0;

    virtual bool processInput(const commonlib::InputEvent &e) = 0;
};


} // end of namespace botlib
} // end of namespace mcdane

#endif

