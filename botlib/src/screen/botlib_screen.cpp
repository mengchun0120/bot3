#include <commonlib_exception.h>
#include <botlib_start_screen.h>

namespace mcdane {
namespace botlib {

Screen* Screen::create(Type type,
                       const commonlib::Vector2& viewportSize,
                       ScreenManager* screenMgr)
{
    Screen* screen = nullptr;
    switch(type)
    {
        case SCREEN_START:
            screen = new StartScreen(viewportSize, screenMgr);
            break;
        case SCREEN_GAME:
            break;
        case SCREEN_SHOW_MAP:
            break;
        default:
            THROW_EXCEPT(commonlib::MyException, "Invalid screen type");
            break;
    }

    return screen;
}

} // end of namespace botlib
} // end of namespace mcdane

