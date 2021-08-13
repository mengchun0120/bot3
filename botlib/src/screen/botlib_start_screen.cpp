#include <commonlib_log.h>
#include <botlib_bot_app.h>
#include <botlib_start_screen.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

StartScreen::StartScreen()
{
}

StartScreen::~StartScreen()
{
}

void StartScreen::update()
{
}

void StartScreen::present()
{
}

bool StartScreen::processInput(const InputEvent &e)
{
#ifdef DESKTOP_APP
    switch (e.type())
    {
        case InputEvent::ET_MOUSE_BUTTON:
            return processMouseButtonEvent(e.mouseButtonEvent());
        case InputEvent::ET_MOUSE_MOVE:
            return processMouseMoveEvent(e.mouseMoveEvent());
        case InputEvent::ET_KEY:
            return processKeyEvent(e.keyEvent());
        default:
            break;
    }
#endif
    return true;
}

#ifdef DESKTOP_APP
bool StartScreen::processMouseButtonEvent(const MouseButtonEvent& e)
{
    return true;
}

bool StartScreen::processMouseMoveEvent(const MouseMoveEvent& e)
{
    return true;
}

bool StartScreen::processKeyEvent(const KeyEvent& e)
{
    BotApp& app = BotApp::getInstance();

    if (GLFW_KEY_ESCAPE == e.key_)
    {
        app.setRunning(false);
        return false;
    }
    return true;
}
#endif

} // end of namespace botlib
} // end of namespace mcdane

