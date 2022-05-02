#include <iostream>
#include <commonlib_exception.h>
#include <commonlib_string_utils.h>
#include <botlib_game_map_loader.h>
#include <botlib_context.h>
#include <botlib_player.h>
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

    const GameScreenConfig& cfg = Context::gameScreenConfig();

    loadMap(viewportSize, cfg.mapFile());
    objDumper_.init(cfg.dumperPoolSize());
}

void GameScreen::update(float delta)
{
    updatePlayer(delta);
    clearMapUpdated();
    updateObjects(delta);
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

void GameScreen::loadMap(const Vector2& viewportSize,
                         const std::string& mapFile)
{
    GameMapLoader loader(viewportSize[0], viewportSize[1]);

    loader.load(map_, mapFile);
}

bool GameScreen::processMouseButton(const MouseButtonEvent& e)
{
    if (e.button_ == GLFW_MOUSE_BUTTON_RIGHT && e.action_ == GLFW_PRESS)
    {
        Player* player = map_.player();
        if (player && player->state() != GameObjectState::ALIVE)
        {
            return true;
        }

        Vector2 p{e.x_, e.y_};
        p += map_.viewportAnchor();

        player->setDest(p);
        player->setMovingEnabled(true);
    }

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

void GameScreen::updatePlayer(float delta)
{
    Player* player = map_.player();
    if (!player || player->state() == GameObjectState::DEAD)
    {
        return;
    }

    player->update(map_, delta);
    map_.setViewportOrigin(player->x(), player->y());
}

void GameScreen::clearMapUpdated()
{
    objFlagResetter_.reset(GameObject::FLAG_UPDATED, false);
    map_.accessRegion(map_.presentArea(), objFlagResetter_, false);
}

void GameScreen::updateObjects(float delta)
{
    objUpdater_.reset(delta);
    map_.accessRegion(map_.presentArea(), objUpdater_, true);
}

} // end of namespace botlib
} // end of namespace mcdane

