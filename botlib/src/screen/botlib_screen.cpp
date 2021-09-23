#include <commonlib_exception.h>
#include <botlib_start_screen.h>

namespace mcdane {
namespace botlib {

Screen* Screen::create(ScreenType type,
                       const commonlib::Vector2& viewportSize,
                       const AppActions& actions)
{
    Screen* screen = nullptr;
    switch(type)
    {
        case ScreenType::START:
            screen = new StartScreen(viewportSize, actions);
            break;
        case ScreenType::GAME:
            break;
        case ScreenType::SHOW_MAP:
            break;
        default:
            THROW_EXCEPT(commonlib::MyException, "Invalid screen type");
            break;
    }

    return screen;
}

Screen::Screen(const AppActions& actions)
    : actions_(actions)
{
}

} // end of namespace botlib
} // end of namespace mcdane

