#include <iostream>
#include <commonlib_exception.h>
#include <commonlib_string_utils.h>
#include <botlib_game_map_loader.h>
#include <botlib_context.h>
#include <botlib_skill_with_cost.h>
#include <botlib_move_skill.h>
#include <botlib_skill_with_cost.h>
#include <botlib_player.h>
#include <botlib_game_screen.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

GameScreen::GameScreen(const commonlib::Vector2 &viewportSize,
                       const AppActions actions,
                       ScreenType nextScreenType)
{
    init(viewportSize, actions);
}

void GameScreen::init(const Vector2 &viewportSize,
                      const AppActions actions,
                      ScreenType nextScreenType)
{
    if (viewportSize[0] <= 0.0f || viewportSize[1] <= 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid viewportSize " + stringVal(viewportSize));
    }

    Screen::init(actions);

    const GameScreenConfig &cfg = Context::gameScreenConfig();

    nextScreenType_ = nextScreenType;
    cxt_.init(&map_, cfg.gameObjItemPoolSize(), cfg.missilePoolSize());
    loadMap(viewportSize, cfg.mapFile());
    viewportSize_ = viewportSize;
    overlayViewportOrigin_ = viewportSize / 2.0f;
    initProgressBar();
    initMessageBox();
    initAIRobotCount();
    initGoodiePies();
    moveOutRegions_.resize(4);
#ifdef __ANDROID__
    initGameNavigator();
#endif
    resetSkillButtonPos();

    LOG_INFO << "GameScreen initialized" << LOG_END;
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
    updateNonPlayerObjects();

    if (map_.player())
    {
        updateProgressBar();
    }

    int moveOutRegionCount = diff(moveOutRegions_, prevArea, map_.presentArea());
    if (moveOutRegionCount > 0)
    {
        clearObjectsFromMoveOutRegion(moveOutRegionCount);
    }

    if (!cxt_.dumper().empty())
    {
        cxt_.dumper().clear(map_);
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

bool GameScreen::processInputEndGame(const commonlib::InputEvent &e)
{
    msgBox_.process(e);

    if (msgBox_.buttonClicked() != MessageBox::BUTTON_OK)
    {
        return true;
    }

    if (nextScreenType_ != ScreenType::NONE)
    {
        if (actions_.switchAction_)
        {
            actions_.switchAction_(nextScreenType_);
        }
    }
    else
    {
        if (actions_.exitAction_)
        {
            actions_.exitAction_();
        }
    }

    return true;
}


#ifdef DESKTOP_APP
bool GameScreen::processInputGame(const commonlib::InputEvent &e)
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

bool GameScreen::processMouseButton(const MouseButtonEvent &e)
{
    if (!isPlayerAvailable())
    {
        return true;
    }

    if (e.button_ == GLFW_MOUSE_BUTTON_LEFT && e.action_ == GLFW_PRESS)
    {
        Vector2 p{e.x_, e.y_};
        p += map_.viewportAnchor();
        map_.player()->setDest(p);
    }
    else if (e.button_ == GLFW_MOUSE_BUTTON_RIGHT && e.action_ == GLFW_PRESS)
    {
        enableSkillForInput(GLFW_MOUSE_BUTTON_RIGHT);
    }

    return true;
}

bool GameScreen::processMouseMove(const MouseMoveEvent &e)
{
    if (!isPlayerAvailable())
    {
        return true;
    }

    if (map_.player()->isSkillEnabled(SkillType::MOVE))
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

bool GameScreen::processKey(const KeyEvent &e)
{
    if (!isPlayerAvailable())
    {
        return true;
    }

    if (e.action_ == GLFW_PRESS)
    {
        enableSkillForInput(e.key_);
    }

    return true;
}

void GameScreen::enableSkillForInput(int input)
{
    Skill *skill = map_.player()->findSkillForInput(input);
    if (skill)
    {
        skill->setEnabled(true);
    }
}

#elif __ANDROID__
void GameScreen::initGameNavigator()
{
    const GameScreenConfig &cfg = Context::gameScreenConfig();

    auto steerFunc = [&](const Vector2 &direction)
    {
        onSteer(direction);
    };
    auto toggleFunc = [&](bool greenOrRed)
    {
        onToggle(greenOrRed);
    };

    navigator_.init(cfg.navigatorLeftSpacing(), cfg.navigatorBottomSpacing(),
                    steerFunc, toggleFunc);
}

bool GameScreen::processInputGame(const commonlib::InputEvent &e)
{
    if (!map_.player())
    {
        return true;
    }

    if (navigator_.containPos(e.x_, e.y_))
    {
        if (e.type_ == InputEvent::POINTER_DOWN)
        {
            navigator_.onPointerDown(e.x_, e.y_);
        }
        else if (e.type_ == InputEvent::POINTER_MOVE)
        {
            navigator_.onPointerOver(e.x_, e.y_);
        }
    }
    else if (e.type_ == InputEvent::POINTER_DOWN)
    {
        onSkillButtonPressed(e.x_, e.y_);
    }

    return true;
}

void GameScreen::onSteer(const Vector2 &direction)
{
    map_.player()->setDirection(direction);
}

void GameScreen::onToggle(bool greenOrRed)
{
    map_.player()->setSkillEnabled(SkillType::MOVE, greenOrRed);
}

void GameScreen::onSkillButtonPressed(float x, float y)
{
    int skillCount = map_.player()->skillCount();
    Skill *skill;
    SkillButton *button;

    for (int i = 0; i < skillCount; ++i)
    {
        skill = map_.player()->skill(i);
        if (!isSkillWithCost(skill->type()))
        {
            continue;
        }

        button = static_cast<SkillWithCost*>(skill)->button();
        if (button->containPos(x, y))
        {
            button->onPointerDown(x, y);
            return;
        }
    }
}
#endif

void GameScreen::onViewportChange(float width, float height)
{
    LOG_INFO << "onViewportChange " << width << " " << height << LOG_END;

    viewportSize_[0] = width;
    viewportSize_[1] = height;
    overlayViewportOrigin_ = viewportSize_ / 2.0f;
    map_.resetViewport(width, height);
    resetOverlayPos();

    LOG_INFO << "onViewportChange finished" << LOG_END;
}

void GameScreen::loadMap(const Vector2 &viewportSize,
                         const std::string &mapFile)
{
    GameMapLoader loader(viewportSize[0], viewportSize[1], cxt_.factory());
    loader.load(map_, mapFile);
}

void GameScreen::initProgressBar()
{
    const GameScreenConfig &cfg = Context::gameScreenConfig();
    const GameLib &lib = Context::gameLib();

    const ProgressBarTemplate *armorBarTemplate =
                             lib.findProgressBarTemplate("armor_progress_bar");
    if (!armorBarTemplate)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Failed to find armor_progress_bar");
    }

    const ProgressBarTemplate *energyBarTemplate =
                             lib.findProgressBarTemplate("energy_progress_bar");
    if (!energyBarTemplate)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Failed to find energy_progress_bar");
    }

    const Vector2 &armorBarMargin = cfg.armorProgressBarMargin();
    const Vector2 &energyBarMargin = cfg.energyProgressBarMargin();
    Vector2 armorBarPos{armorBarMargin[0], viewportSize_[1] - armorBarMargin[1]};
    Vector2 energyBarPos{energyBarMargin[0], viewportSize_[1] - energyBarMargin[1]};

    armorProgressBar_.init(armorBarTemplate, armorBarPos);
    energyProgressBar_.init(energyBarTemplate, energyBarPos);
}

void GameScreen::initMessageBox()
{
    const GameScreenConfig &cfg = Context::gameScreenConfig();

    msgBox_.init(viewportSize_[0] / 2.0f, viewportSize_[1] / 2.0f,
                 cfg.msgBoxWidth(), cfg.msgBoxHeight(),
                 "", MessageBox::BUTTON_OK);
}

void GameScreen::initGoodiePies()
{
    resetGoodiePiePos();
    createGoodiePies();
}

void GameScreen::initAIRobotCount()
{
    const GameScreenConfig &cfg = Context::gameScreenConfig();
    aiRobotCountIcon_.init(cfg.aiRobotCountIconTemplate());
    resetAIRobotCountPos();
}

void GameScreen::createGoodiePies()
{
    const GameScreenConfig &cfg = Context::gameScreenConfig();
    int goodieCount = lastingGoodieTypeCount();

    goodiePies_.resize(goodieCount);
    for (int i = 0; i < goodieCount; ++i)
    {
        goodiePies_[i].init(cfg.goodiePieTemplate(i));
    }
}

void GameScreen::updatePlayer()
{
    Player *player = map_.player();
    player->update(cxt_);
    map_.setViewportOrigin(player->x(), player->y());
}

void GameScreen::clearUpdateFlags()
{
    auto clearUpdateFlag = [](GameObject *obj)->bool
    {
        obj->setUpdated(false);
        return true;
    };

    map_.traverse(map_.presentArea(), clearUpdateFlag);
}

void GameScreen::updateNonPlayerObjects()
{
    auto updater = [this](GameObject *obj)->bool
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

void GameScreen::presentOverlay()
{
    SimpleShaderProgram &program = Context::graphics().simpleShader();
    const TextSystem &textSys = Context::graphics().textSys();
    const GameScreenConfig &cfg = Context::gameScreenConfig();

    program.use();
    program.setViewportOrigin(overlayViewportOrigin_);
    program.setViewportSize(viewportSize_);

    if (map_.player())
    {
        presentGoodiePies();
#ifdef __ANDROID__
        navigator_.present();
#endif
        presentSkillButtons();
    }

    program.setAlpha(1.0f);

    armorProgressBar_.present();
    energyProgressBar_.present();

    aiRobotCountIcon_.present(aiRobotIconPos_);
    textSys.draw(program, map_.aiRobotCountStr(), aiRobotCountPos_,
                 cfg.aiRobotCountTextSize(), &cfg.aiRobotCountTextColor());

    if (msgBox_.visible())
    {
        msgBox_.present();
    }
}

void GameScreen::presentGoodiePies()
{
    const GoodieEffectItem *g;
    int i = 0;
    for (g = map_.player()->firstGoodieEffect(); g; g = g->next(), ++i)
    {
        const GoodieEffect &effect = g->item();
        int idx = lastingGoodieTypeIndex(effect.type());
        ProgressPie &pie = goodiePies_[idx];

        pie.setFinishedRatio(effect.finishedRatio());
        pie.present(goodiePiePos_[i]);
    }
}

void GameScreen::presentSkillButtons()
{
    Player *player = map_.player();
    int skillCount = player->skillCount();
    Skill *skill;
    SkillWithCost *skill1;

    for (int i = 0; i < skillCount; ++i)
    {
        skill = player->skill(i);
        if (isSkillWithCost(skill->type()))
        {
            skill1 = static_cast<SkillWithCost*>(skill);
            skill1->button()->present();
        }
    }
}

void GameScreen::showVictory()
{
    const GameScreenConfig &cfg = Context::gameScreenConfig();
    msgBox_.setText(cfg.victoryMsg());
    msgBox_.setVisible(true);
}

void GameScreen::showFail()
{
    const GameScreenConfig &cfg = Context::gameScreenConfig();
    msgBox_.setText(cfg.failMsg());
    msgBox_.setVisible(true);
}

void GameScreen::clearObjectsFromMoveOutRegion(int moveOutRegionCount)
{
    auto remover = [this](GameObject *obj)->bool
    {
        if (obj->state() != GameObjectState::DEAD && obj->canBeDumped(map_))
        {
            cxt_.dumper().add(obj);
        }

        return true;
    };

    for (int i = 0; i < moveOutRegionCount; ++i)
    {
        map_.traverse(moveOutRegions_[i], remover);
    }
}

void GameScreen::resetOverlayPos()
{
    LOG_INFO << "resetOverlay 1" << LOG_END;

    resetMessageBoxPos();
    resetProgressBarPos();
    resetGoodiePiePos();
    resetAIRobotCountPos();
    resetSkillButtonPos();

    LOG_INFO << "resetOverlay 2" << LOG_END;
}

void GameScreen::resetMessageBoxPos()
{
    msgBox_.setPos(viewportSize_[0]/2.0f, viewportSize_[1]/2.0f);
}

void GameScreen::resetProgressBarPos()
{
    const GameScreenConfig &cfg = Context::gameScreenConfig();
    const Vector2 &armorBarMargin = cfg.armorProgressBarMargin();
    const Vector2 &energyBarMargin = cfg.energyProgressBarMargin();
    Vector2 armorBarPos{armorBarMargin[0], viewportSize_[1] - armorBarMargin[1]};
    Vector2 energyBarPos{energyBarMargin[0], viewportSize_[1] - energyBarMargin[1]};

    armorProgressBar_.setPos(armorBarPos);
    energyProgressBar_.setPos(energyBarPos);
}

void GameScreen::resetGoodiePiePos()
{
    const GameScreenConfig &cfg = Context::gameScreenConfig();
    int goodieCount = lastingGoodieTypeCount();
    float radius = cfg.goodiePieTemplate(0)->radius();
    float x, y, spacing;

    y = viewportSize_[1] - cfg.goodieTopMargin() - radius;

    x = viewportSize_[0] - cfg.goodieRightMargin() -
        (goodieCount - 1) * cfg.goodieSpacing() - (2*goodieCount - 1) * radius;

    spacing = 2 * radius + cfg.goodieSpacing();

    goodiePiePos_.resize(goodieCount);
    for (int i = 0; i < goodieCount; ++i)
    {
        goodiePiePos_[i].init({x, y});
        x += spacing;
    }
}

void GameScreen::resetAIRobotCountPos()
{
    const GameScreenConfig &cfg = Context::gameScreenConfig();
    const Vector2 &iconMargin = cfg.aiRobotCountIconMargin();
    const Vector2 &textMargin = cfg.aiRobotCountTextMargin();

    aiRobotIconPos_[0] = iconMargin[0];
    aiRobotIconPos_[1] = viewportSize_[1] - iconMargin[1];
    aiRobotCountPos_[0] = textMargin[0];
    aiRobotCountPos_[1] = viewportSize_[1] - textMargin[1];
}

void GameScreen::resetSkillButtonPos()
{
    if (map_.player())
    {
        map_.player()->resetSkillButtonPos(viewportSize_);
    }
}

} // end of namespace botlib
} // end of namespace mcdane
