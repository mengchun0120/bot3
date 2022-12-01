#ifndef INCLUDED_BOTLIB_SCREEN_MANAGER_H
#define INCLUDED_BOTLIB_SCREEN_MANAGER_H

#include <commonlib_vector.h>
#include <botlib_screen.h>

namespace mcdane {
namespace botlib {

class ScreenManager {
public:
    ScreenManager();

    ~ScreenManager();

    void init2(Screen* startScreen);

    void init(ScreenType startScreenType,
              const commonlib::Vector2& viewportSize,
              const AppActions& actions);

    void update(float delta);

    void present();

    bool processInput(const commonlib::InputEvent &e);

    void switchScreen2(Screen* newScreen);

    void switchScreen(ScreenType type);

    void postProcess();

    Screen& getCurScreen()
    {
        return *curScreen_;
    }

private:
    Screen* createScreen(ScreenType screenType);

private:
    Screen* prevScreen_;
    Screen* curScreen_;
    ScreenType curScreenType_;
    commonlib::Vector2 viewportSize_;
    AppActions actions_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

