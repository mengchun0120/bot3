#include <commonlib_exception.h>
#include <commonlib_string_utils.h>
#include <botlib_game_map_loader.h>
#include <botlib_context.h>
#include <botlib_game_screen.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

GameScreen::GameScreen(const Vector2& viewportSize,
                       const AppActions actions)
{
    init(viewportSize, actions);
}

GameScreen::~GameScreen()
{
}

void GameScreen::init(const Vector2& viewportSize,
                      const AppActions actions)
{
    Screen::init(actions);

    if (viewportSize[0] <= 0.0f || viewportSize[1] <= 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid viewportSize " + stringVal(viewportSize));
    }

    GameMapLoader loader(viewportSize[0], viewportSize[1]);
    const GameScreenConfig& cfg = Context::gameScreenConfig();

    loader.load(map_, cfg.mapFile());
}

void GameScreen::update()
{
}

void GameScreen::present()
{
    map_.present();
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

bool GameScreen::processMouseButton(const MouseButtonEvent& e)
{
    return true;
}

bool GameScreen::processMouseMove(const MouseMoveEvent& e)
{
    return true;
}

bool GameScreen::processKey(const KeyEvent& e)
{
    return true;
}

} // end of namespace botlib
} // end of namespace mcdane

