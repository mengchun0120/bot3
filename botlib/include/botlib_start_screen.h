#ifndef INCLUDED_BOTLIB_START_SCREEN_H
#define INCLUDED_BOTLIB_START_SCREEN_H

#include <botlib_screen.h>

namespace mcdane {
namespace botlib {

class StartScreen: public Screen {
public:
    StartScreen();

    ~StartScreen() override;

    void update() override;

    void present() override;

    bool processInput(const commonlib::InputEvent &e) override;

private:
#ifdef DESKTOP_APP
    bool processMouseButtonEvent(const commonlib::MouseButtonEvent& e);

    bool processMouseMoveEvent(const commonlib::MouseMoveEvent& e);

    bool processKeyEvent(const commonlib::KeyEvent& e);
#endif
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

