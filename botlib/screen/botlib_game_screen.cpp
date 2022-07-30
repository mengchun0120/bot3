#include <iostream>
#include <commonlib_exception.h>
#include <commonlib_string_utils.h>
#include <botlib_game_map_loader.h>
#include <botlib_context.h>
#include <botlib_player.h>
#include <botlib_game_object_flag_resetter.h>
#include <botlib_game_object_updater.h>
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
    viewportSize_ = viewportSize;
    overlayViewportOrigin_ = viewportSize / 2.0f;
    initProgressBar();
}

void GameScreen::update(float timeDelta)
{
    if (map_.player())
    {
        updatePlayer(timeDelta);
    }

    clearMapUpdated();
    updateObjects(timeDelta);

    if (map_.player())
    {
        updateProgressBar();
    }

    if (!objDumper_.empty())
    {
        objDumper_.clear(map_);
    }
}

void GameScreen::present()
{
    glClear(GL_COLOR_BUFFER_BIT);
    map_.present();
    if (map_.player())
    {
        presentOverlay();
    }
    glFlush();
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

void GameScreen::initProgressBar()
{
    const GameScreenConfig& cfg = Context::gameScreenConfig();
    const GameLib& lib = Context::gameLib();

    const ProgressBarTemplate* armorBarTemplate =
                             lib.findProgressBarTemplate("armor_progress_bar");
    if (!armorBarTemplate)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Failed to find armor_progress_bar");
    }

    const ProgressBarTemplate* energyBarTemplate =
                             lib.findProgressBarTemplate("energy_progress_bar");
    if (!energyBarTemplate)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Failed to find energy_progress_bar");
    }

    const Vector2& armorBarMargin = cfg.armorProgressBarMargin();
    const Vector2& energyBarMargin = cfg.energyProgressBarMargin();
    Vector2 armorBarPos{armorBarMargin[0], viewportSize_[1] - armorBarMargin[1]};
    Vector2 energyBarPos{energyBarMargin[0], viewportSize_[1] - energyBarMargin[1]};

    armorProgressBar_.init(armorBarTemplate, armorBarPos);
    energyProgressBar_.init(energyBarTemplate, energyBarPos);
}

bool GameScreen::processMouseButton(const MouseButtonEvent& e)
{
    if (!isPlayerAvailable())
    {
        return true;
    }

    if (e.button_ == GLFW_MOUSE_BUTTON_LEFT)
    {
        map_.player()->setShootingEnabled(e.action_ == GLFW_PRESS);
    }

    return true;
}

bool GameScreen::processMouseMove(const MouseMoveEvent& e)
{
    if (!isPlayerAvailable())
    {
        return true;
    }

    Vector2 p{e.x_, e.y_};
    p += map_.viewportAnchor();

    if (fuzzyEqual(p, map_.player()->pos(), 0.2f))
    {
        return true;
    }

    Vector2 direction = normalize(p - map_.player()->pos());
    map_.player()->setDirection(direction);

    return true;
}

bool GameScreen::processKey(const KeyEvent& e)
{
    switch(e.key_)
    {
        case GLFW_KEY_A:
        {
            processFireKey(e);
            break;
        }
        case GLFW_KEY_F:
        {
            processForwardKey(e);
            break;
        }
        default:
            break;
    }

    return true;
}

void GameScreen::processFireKey(const KeyEvent& e)
{
    if (!isPlayerAvailable())
    {
        return;
    }

    map_.player()->setShootingEnabled(e.action_ == GLFW_PRESS);
}

void GameScreen::processForwardKey(const KeyEvent& e)
{
    if (!isPlayerAvailable() || e.action_ != GLFW_RELEASE)
    {
        return;
    }

    bool enabled = !map_.player()->movingEnabled();
    map_.player()->setMovingEnabled(enabled);
}

void GameScreen::updatePlayer(float timeDelta)
{
    Player* player = map_.player();
    player->update(map_, objDumper_, timeDelta);
    map_.setViewportOrigin(player->x(), player->y());
}

void GameScreen::clearMapUpdated()
{
    GameObjectFlagResetter flagResetter(GameObject::FLAG_UPDATED, false);
    map_.accessRegion(map_.presentArea(), flagResetter);
}

void GameScreen::updateObjects(float timeDelta)
{
    GameObjectUpdater updater(map_, objDumper_, timeDelta);
    map_.accessRegion(map_.presentArea(), updater);
}

void GameScreen::updateProgressBar()
{
    armorProgressBar_.setRatio(map_.player()->armorRatio());
    energyProgressBar_.setRatio(map_.player()->energyRatio());
}

void GameScreen::presentOverlay()
{
    SimpleShaderProgram& program = Context::graphics().simpleShader();
    program.use();
    program.setViewportOrigin(overlayViewportOrigin_);
    program.setViewportSize(viewportSize_);

    map_.player()->presentGoodies();
    armorProgressBar_.present();
    energyProgressBar_.present();
}

} // end of namespace botlib
} // end of namespace mcdane

