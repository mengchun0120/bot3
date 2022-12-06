#include <iostream>
#include <commonlib_exception.h>
#include <commonlib_string_utils.h>
#include <botlib_game_map_loader.h>
#include <botlib_context.h>
#include <botlib_player.h>
#include <botlib_game_utils.h>
#include <botlib_game_screen.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

GameScreen::GameScreen(const commonlib::Vector2& viewportSize,
                       const AppActions actions,
                       ScreenType nextScreenType)
{
    init(viewportSize, actions);
}

void GameScreen::init(const Vector2& viewportSize,
                      const AppActions actions,
                      ScreenType nextScreenType)
{
    if (viewportSize[0] <= 0.0f || viewportSize[1] <= 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid viewportSize " + stringVal(viewportSize));
    }

    Screen::init(actions);

    const GameScreenConfig& cfg = Context::gameScreenConfig();

    nextScreenType_ = nextScreenType;
    loadMap(viewportSize, cfg.mapFile());
    objDumper_.init(cfg.dumperPoolSize());
    viewportSize_ = viewportSize;
    overlayViewportOrigin_ = viewportSize / 2.0f;
    cxt_.init(&map_, &objDumper_, std::bind(&GameScreen::onAIRobotDeath, this));
    initProgressBar();
    initMessageBox();
    initAIRobotCount();
    moveOutRegions_.resize(4);
}

void GameScreen::update(float timeDelta)
{
    if (msgBox_.visible())
    {
        return;
    }

    cxt_.setTimeDelta(timeDelta);

    Region<int> prevArea = map_.presentArea();

    if (map_.player())
    {
        updatePlayer();
    }

    clearUpdateFlags();
    updateObjects();

    if (map_.player())
    {
        updateProgressBar();
    }

    int moveOutRegionCount = diff(moveOutRegions_, prevArea, map_.presentArea());
    if (moveOutRegionCount > 0)
    {
        clearObjectsFromMoveOutRegion(moveOutRegionCount);
    }

    if (!objDumper_.empty())
    {
        objDumper_.clear(map_);
    }

    if (map_.player() == nullptr)
    {
        showFail();
    }
    else if(map_.aiRobotCount() == 0)
    {
        showVictory();
    }
}

void GameScreen::present()
{
    glClear(GL_COLOR_BUFFER_BIT);

    map_.present();
    presentOverlay();

    glFlush();
}

bool GameScreen::processInput(const InputEvent &e)
{
    if (!msgBox_.visible())
    {
        return processInputGame(e);
    }

    return processInputEndGame(e);
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

void GameScreen::initMessageBox()
{
    const GameScreenConfig& cfg = Context::gameScreenConfig();

    msgBox_.init(viewportSize_[0] / 2.0f, viewportSize_[1] / 2.0f,
                 cfg.msgBoxWidth(), cfg.msgBoxHeight(),
                 "", MessageBox::BUTTON_OK);
}

void GameScreen::initAIRobotCount()
{
    const GameScreenConfig& cfg = Context::gameScreenConfig();
    const Vector2& iconMargin = cfg.aiRobotCountIconMargin();
    const Vector2& textMargin = cfg.aiRobotCountTextMargin();
    Vector2 iconPos{iconMargin[0], viewportSize_[1] - iconMargin[1]};

    aiRobotCountIcon_.init(cfg.aiRobotCountIconTemplate(), iconPos);
    aiRobotCountPos_.init({textMargin[0], viewportSize_[1] - textMargin[1]});
    updateAIRobotCount();
}

bool GameScreen::processInputEndGame(const commonlib::InputEvent& e)
{
    msgBox_.process(e);

    if (msgBox_.buttonClicked() != MessageBox::BUTTON_OK)
    {
        return true;
    }

    if (nextScreenType_ != ScreenType::NONE)
    {
        actions_.switchAction_(nextScreenType_);
    }
    else
    {
        actions_.exitAction_();
    }

    return true;
}

bool GameScreen::processInputGame(const commonlib::InputEvent& e)
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

void GameScreen::updatePlayer()
{
    Player* player = map_.player();
    player->update(cxt_);
    map_.setViewportOrigin(player->x(), player->y());
}

void GameScreen::clearUpdateFlags()
{
    auto clearUpdateFlag = [](GameObject *obj)->bool
    {
        obj->setFlag(GameObject::FLAG_UPDATED, false);
        return true;
    };

    map_.traverse(map_.presentArea(), clearUpdateFlag);
}

void GameScreen::updateObjects()
{
    auto updater = [this](GameObject* obj)->bool
    {
        if (obj->updated() && obj->state() == GameObjectState::DEAD)
        {
            return true;
        }

        obj->update(cxt_);
        return true;
    };

    map_.traverse(map_.presentArea(), updater);
}

void GameScreen::updateProgressBar()
{
    armorProgressBar_.setRatio(map_.player()->armorRatio());
    energyProgressBar_.setRatio(map_.player()->energyRatio());
}

void GameScreen::updateAIRobotCount()
{
    aiRobotCountStr_ = std::to_string(map_.aiRobotCount());
}

void GameScreen::presentOverlay()
{
    SimpleShaderProgram& program = Context::graphics().simpleShader();
    const TextSystem& textSys = Context::graphics().textSys();
    const GameScreenConfig& cfg = Context::gameScreenConfig();

    program.use();
    program.setViewportOrigin(overlayViewportOrigin_);
    program.setViewportSize(viewportSize_);

    if (map_.player())
    {
        map_.player()->presentGoodies();
    }

    program.setAlpha(1.0f);

    armorProgressBar_.present();
    energyProgressBar_.present();

    aiRobotCountIcon_.present();
    textSys.draw(program, aiRobotCountStr_, aiRobotCountPos_,
                 cfg.aiRobotCountTextSize(), &cfg.aiRobotCountTextColor());

    if (msgBox_.visible())
    {
        msgBox_.present();
    }
}

void GameScreen::showVictory()
{
    const GameScreenConfig& cfg = Context::gameScreenConfig();
    msgBox_.setText(cfg.victoryMsg());
    msgBox_.setVisible(true);
}

void GameScreen::showFail()
{
    const GameScreenConfig& cfg = Context::gameScreenConfig();
    msgBox_.setText(cfg.failMsg());
    msgBox_.setVisible(true);
}

void GameScreen::onAIRobotDeath()
{
    map_.decreaseAIRobotCount();
    updateAIRobotCount();
}

void GameScreen::clearObjectsFromMoveOutRegion(int moveOutRegionCount)
{
    auto remover = [this](GameObject* obj)->bool
    {
        if (obj->state() != GameObjectState::DEAD && obj->canBeDumped(map_))
        {
            objDumper_.add(obj);
        }

        return true;
    };

    for (int i = 0; i < moveOutRegionCount; ++i)
    {
        map_.traverse(moveOutRegions_[i], remover);
    }
}

} // end of namespace botlib
} // end of namespace mcdane

