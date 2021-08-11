#include <commonlib_exception.h>
#include <commonlib_start_screen.h>

namespace mcdane {
namespace commonlib {

Screen* Screen::create(Type type)
{
    Screen* screen = nullptr;
    switch(type)
    {
        case SCREEN_START:
            screen = new StartScreen();
            break;
        case SCREEN_GAME:
            break;
        case SCREEN_SHOW_MAP:
            break;
        default:
            THROW_EXCEPT(MyException, "Invalid screen type");
            break;
    }

    return screen;
}

} // end of namespace commonlib
} // end of namespace mcdane

