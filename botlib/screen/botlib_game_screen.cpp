#include <commonlib_exception.h>
#include <commonlib_string_utils.h>
#include <botlib_game_screen.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

GameScreen::GameScreen(const Vector2& viewportSize,
                       const AppActions actions,
                       const GameScreenConfig& cfg)
{
    init(viewportSize, actions, cfg);
}

GameScreen::~GameScreen()
{
}

void GameScreen::init(const commonlib::Vector2& viewportSize,
                      const AppActions actions,
                      const GameScreenConfig& cfg)
{
    Screen::init(actions);
    cfg_ = cfg;

    if (viewportSize[0] <= 0.0f || viewportSize[1] <= 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid viewportSize " + stringVal(viewportSize));
    }
}

void GameScreen::update()
{
}

void GameScreen::present()
{
}

bool GameScreen::processInput(const InputEvent &e)
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
                         std::to_string(static_cast<int>(e.type())));
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

