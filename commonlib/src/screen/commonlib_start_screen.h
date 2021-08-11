#ifndef INCLUDED_COMMONLIB_START_SCREEN_H
#define INCLUDED_COMMONLIB_START_SCREEN_H

#include <commonlib_screen.h>

namespace mcdane {
namespace commonlib {

class StartScreen: public Screen {
public:
    StartScreen();

    ~StartScreen() override;

    void update() override;

    void present() override;

    bool processInput(const InputEvent &e) override;

private:
#ifdef DESKTOP_APP
    bool processMouseButtonEvent(const MouseButtonEvent& e);

    bool processMouseMoveEvent(const MouseMoveEvent& e);

    bool processKeyEvent(const KeyEvent& e);
#endif
};

} // end of namespace commonlib
} // end of namespace mcdane

#endif

