#ifndef INCLUDED_COMMONLIB_SCREEN_MANAGER_H
#define INCLUDED_COMMONLIB_SCREEN_MANAGER_H

#include <commonlib_screen.h>

namespace mcdane {
namespace commonlib {

class ScreenManager {
public:
    ScreenManager();

    ~ScreenManager();

    void init(Screen::Type startScreenType);

    void update();

    void present();

    bool processInput(const InputEvent &e);

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

} // end of namespace commonlib
} // end of namespace mcdane

#endif

