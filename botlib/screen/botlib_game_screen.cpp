#include <iostream>
#include <commonlib_exception.h>
#include <commonlib_string_utils.h>
#include <botlib_game_screen.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

GameScreen::GameScreen(const Vector2& viewportSize,
                       const AppActions actions)
    : Screen(actions)
{
    if (viewportSize[0] <= 0.0f || viewportSize[1] <= 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid viewportSize " + toString(viewportSize));
    }
}

GameScreen::~GameScreen()
{
}

void GameScreen::update()
{
}

void GameScreen::present()
{
}

bool GameScreen::processInput(const commonlib::InputEvent &e)
{
    switch (e.type())
    {
        case EventType::MOUSE_BUTTON:
            return processMouseButton(e.mouseButtonEvent());
        case EventType::MOUSE_MOVE:
            return processMouseMove(e.mouseMoveEvent());
        case EventType::KEY:
            return processKey(e.keyEvent());
        default:
            THROW_EXCEPT(InvalidArgumentException,
                         "Invalid event-type: " +
                            toString(static_cast<int>(e.type())));
    }

    return true;
}

bool GameScreen::processMouseButton(const commonlib::MouseButtonEvent& e)
{
    return true;
}

bool GameScreen::processMouseMove(const commonlib::MouseMoveEvent& e)
{
    return true;
}

bool GameScreen::processKey(const commonlib::KeyEvent& e)
{
    return true;
}

} // end of namespace botlib
} // end of namespace mcdane

