#ifndef INCLUDED_BOTLIB_SCREEN_MANAGER_H
#define INCLUDED_BOTLIB_SCREEN_MANAGER_H

#include <botlib_screen.h>

namespace mcdane {
namespace botlib {

class ScreenManager {
public:
    ScreenManager();

    ~ScreenManager();

    void init(Screen::Type startScreenType);

    void update();

    void present();

    bool processInput(const commonlib::InputEvent &e);

    void switchScreen(Screen::Type type);

    void postProcess();

    Screen& getCurScreen()
    {
        return *curScreen_;
    }

private:
    Screen* prevScreen_;
    Screen* curScreen_;
    Screen::Type curScreenType_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

