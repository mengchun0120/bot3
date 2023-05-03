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

void GameScreen::init(const Vector2 &viewportSize,
                      const AppActions actions,
                      ScreenType nextScreenType,
                      bool exerciseMode)
{
    if (viewportSize[0] <= 0.0f || viewportSize[1] <= 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid viewportSize " + stringVal(viewportSize));
    }

    Screen::init(actions);

    const GameScreenConfig &cfg = Context::gameScreenConfig();

    exerciseMode_ = exerciseMode;
    nextScreenType_ = nextScreenType;
    cxt_.init(&map_, cfg.gameObjItemPoolSize(), cfg.missilePoolSize(),
              exerciseMode);
    loadMap(viewportSize, cfg.mapFile());
    viewportSize_ = viewportSize;
    overlayViewportOrigin_ = viewportSize / 2.0f;
    initMapAccessors();
    initProgressBar();
    initMessageBox();
    initAIRobotCount();
    initGoodiePies();
    initSkillButtons();
    resetSkillButtonPos();
    moveOutRegions_.resize(4);

    LOG_INFO << "GameScreen initialized" << LOG_END;
}

void GameScreen::update(float timeDelta)
{
    if (msgBox_.visible())
    {
        return;
    }

    preUpdate(timeDelta);
    updateObjs();
    clearObjs();
    showMsg();
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
        onPointerDown(e.x_, e.y_);
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
bool GameScreen::processInputGame(const commonlib::InputEvent &e)
{
    if (!map_.player())
    {
        return true;
    }

    if (e.type_ == InputEvent::POINTER_DOWN || e.type_ == InputEvent::POINTER_MOVE)
    {
        if (!onSkillButtonPressed(e.x_, e.y_) && !onObjPressed(e.x_, e.y_))
        {
            onPointerDown(e.x_, e.y_);
        }
    }

    return true;
}

bool GameScreen::onSkillButtonPressed(float x, float y)
{
    for (auto &button : skillButtons_)
    {
        if (button.containPos(x, y))
        {
            button.onPointerDown(x, y);
            return true;
        }
    }

    return false;
}

bool GameScreen::onObjPressed(float x, float y)
{
    Vector2 p{x, y};
    p += map_.viewportAnchor();

    Region<int> area = map_.getTouchArea(p);
    objChooser_.init(p);
    map_.traverse(area, objChooser_, GameMap::LAYER_TILE_GOODIE, 2);

    if (objChooser_.obj())
    {
        onObjSelected(objChooser_.obj());
        return true;
    }

    return false;
}

void GameScreen::onObjSelected(GameObject *o)
{
    Player *player = map_.player();

    player->setSkillEnabled(SkillType::MOVE, false);

    if (o != static_cast<GameObject *>(player))
    {
        Vector2 d = normalize(o->pos() - player->pos());

        player->setDirection(d);
        player->defaultSkill()->setEnabled(true);
    }
}
#endif

void GameScreen::onPointerDown(float x, float y)
{
    Vector2 p{x, y};
    p += map_.viewportAnchor();
    map_.player()->setDest(p);
}

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
    initPlayerGoodieFunc();
}

void GameScreen::initMapAccessors()
{
    flagResetter_.init(GameObjFlag::UPDATED);
    objUpdater_.init(&cxt_);
}

void GameScreen::initPlayerGoodieFunc()
{
    Player::GoodieFunc func = std::bind(&GameScreen::updateGoodiePiePos, this);
    map_.player()->setGoodieFunc(func);
}

void GameScreen::initProgressBar()
{
    const GameScreenConfig &cfg = Context::gameScreenConfig();
    const Vector2 &armorBarMargin = cfg.armorProgressBarMargin();
    const Vector2 &energyBarMargin = cfg.energyProgressBarMargin();
    const Vector2 &hpBarMargin = cfg.hpProgressBarMargin();
    Vector2 armorBarPos{armorBarMargin[0], viewportSize_[1] - armorBarMargin[1]};
    Vector2 energyBarPos{energyBarMargin[0], viewportSize_[1] - energyBarMargin[1]};
    Vector2 hpBarPos{hpBarMargin[0], viewportSize_[1] - hpBarMargin[1]};

    armorProgressBar_.init(cfg.armorProgressBar(), armorBarPos);
    energyProgressBar_.init(cfg.energyProgressBar(), energyBarPos);
    hpProgressBar_.init(cfg.hpProgressBar(), hpBarPos);
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
    calculateGoodiePiePos();
    createGoodiePies();
}

void GameScreen::calculateGoodiePiePos()
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

void GameScreen::initAIRobotCount()
{
    const GameScreenConfig &cfg = Context::gameScreenConfig();
    resetAIRobotCountPos();
    aiRobotCountIcon_.init(cfg.aiRobotCountIconTemplate(), &aiRobotIconPos_);
}

void GameScreen::initSkillButtons()
{
    const GameScreenConfig &cfg = Context::gameScreenConfig();
    float y = cfg.skillButtonBottomSpacing();
    float x = viewportSize_[0] - cfg.skillButtonRightSpacing();
    int skillCount = map_.player()->skillCount();

    for (int i = skillCount - 1; i >= 0; --i)
    {
        if (addSkillButton(map_.player()->skill(i), x, y))
        {
            x -= cfg.skillButtonSpacing();
        }
    }
}

bool GameScreen::addSkillButton(Skill *skill,
                                float x,
                                float y)
{
    if (!isSkillWithCost(skill->type()))
    {
        return false;
    }

    SkillWithCost *skill1 = static_cast<SkillWithCost *>(skill);
    const SkillWithCostTemplate *t = skill1->getTemplate();
    if (!t->pieTemplate())
    {
        return false;
    }

    auto action = [this, skill1](SkillButton &button)
    {
        if (map_.player())
        {
            skill1->setEnabled(true);
        }
    };

    skillButtons_.emplace_back();
    skillButtons_.back().init(x, y, t->pieTemplate(), action, skill1);

    return true;
}

void GameScreen::preUpdate(float timeDelta)
{
    cxt_.setTimeDelta(timeDelta);
    prevArea_ = map_.presentArea();
}

void GameScreen::updateObjs()
{
    Player *player = map_.player();
    if (player)
    {
        updatePlayer();
    }

    clearUpdateFlags();
    updateNonPlayerObjects();

    if (player)
    {
        updateOverlay();
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
    map_.traverse(map_.presentArea(), flagResetter_);
}

void GameScreen::updateNonPlayerObjects()
{
    map_.traverse(map_.presentArea(), objUpdater_);
}

void GameScreen::updateOverlay()
{
    updateProgressBar();
    updateSkillButtons();
    if (map_.player()->hasGoodie())
    {
        updateGoodiePieRatio();
    }
}

void GameScreen::updateProgressBar()
{
    armorProgressBar_.setRatio(map_.player()->armorRatio());
    energyProgressBar_.setRatio(map_.player()->energyRatio());
    hpProgressBar_.setRatio(map_.player()->hpRatio());
}

void GameScreen::updateGoodiePieRatio()
{
    const GoodieEffectItem *g;
    for (g = map_.player()->firstGoodieEffect(); g; g = g->next())
    {
        const GoodieEffect &e = g->item();
        ProgressPie &pie = getGoodiePie(e);
        pie.setFinishedRatio(e.finishedRatio());
    }
}

void GameScreen::updateGoodiePiePos()
{
    const GoodieEffectItem *g;
    int i = 0;
    for (g = map_.player()->firstGoodieEffect(); g; g = g->next(), ++i)
    {
        ProgressPie &pie = getGoodiePie(g->item());
        pie.setPos(goodiePiePos_[i]);
    }
}

void GameScreen::updateSkillButtons()
{
    for (auto &button : skillButtons_)
    {
        button.update();
    }
}

void GameScreen::clearObjs()
{
    int moveOutRegionCount = diff(moveOutRegions_, prevArea_, map_.presentArea());
    if (moveOutRegionCount > 0)
    {
        clearObjectsFromMoveOutRegion(moveOutRegionCount);
    }

    if (!cxt_.dumper().empty())
    {
        cxt_.dumper().clear(map_);
    }
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

void GameScreen::showMsg()
{
    if (map_.player() == nullptr)
    {
        showFail();
    }
    else if(map_.aiRobotCount() == 0)
    {
        showVictory();
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

void GameScreen::presentOverlay()
{
    SimpleShaderProgram &program = Context::graphics().simpleShader();

    program.use();
    program.setViewportOrigin(overlayViewportOrigin_);
    program.setViewportSize(viewportSize_);

    if (map_.player())
    {
        presentGoodiePies();
        presentSkillButtons();
    }

    program.setAlpha(1.0f);

    if (map_.player())
    {
        presentProgressBars();
    }

    presentAIRobotCount();

    if (msgBox_.visible())
    {
        msgBox_.present();
    }
}

void GameScreen::presentGoodiePies()
{
    const GoodieEffectItem *g;
    for (g = map_.player()->firstGoodieEffect(); g; g = g->next())
    {
        ProgressPie &pie = getGoodiePie(g->item());
        pie.present();
    }
}

void GameScreen::presentSkillButtons()
{
    for (auto &button : skillButtons_)
    {
        button.present();
    }
}

void GameScreen::presentProgressBars()
{
    armorProgressBar_.present();
    energyProgressBar_.present();
    hpProgressBar_.present();
}

void GameScreen::presentAIRobotCount()
{
    SimpleShaderProgram &program = Context::graphics().simpleShader();
    const TextSystem &textSys = Context::graphics().textSys();
    const GameScreenConfig &cfg = Context::gameScreenConfig();

    aiRobotCountIcon_.present();
    textSys.draw(program, map_.aiRobotCountStr(), aiRobotCountPos_,
                 cfg.aiRobotCountTextSize(), &cfg.aiRobotCountTextColor());
}

void GameScreen::resetOverlayPos()
{
    resetMessageBoxPos();
    resetProgressBarPos();
    resetGoodiePiePos();
    resetAIRobotCountPos();
    resetSkillButtonPos();
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
    const Vector2 &hpBarMargin = cfg.hpProgressBarMargin();
    Vector2 armorBarPos{armorBarMargin[0], viewportSize_[1] - armorBarMargin[1]};
    Vector2 energyBarPos{energyBarMargin[0], viewportSize_[1] - energyBarMargin[1]};
    Vector2 hpBarPos{hpBarMargin[0], viewportSize_[1] - hpBarMargin[1]};

    armorProgressBar_.setPos(armorBarPos);
    energyProgressBar_.setPos(energyBarPos);
    hpProgressBar_.setPos(hpBarPos);
}

void GameScreen::resetGoodiePiePos()
{
    calculateGoodiePiePos();
    updateGoodiePiePos();
}

void GameScreen::resetAIRobotCountPos()
{
    const GameScreenConfig &cfg = Context::gameScreenConfig();
    const Vector2 &iconMargin = cfg.aiRobotCountIconMargin();
    const Vector2 &textMargin = cfg.aiRobotCountTextMargin();

    aiRobotIconPos_[0] = iconMargin[0];
    aiRobotIconPos_[1] = viewportSize_[1] - iconMargin[1];
    aiRobotCountIcon_.setPos(aiRobotIconPos_);
    aiRobotCountPos_[0] = textMargin[0];
    aiRobotCountPos_[1] = viewportSize_[1] - textMargin[1];
}

void GameScreen::resetSkillButtonPos()
{
    if (!map_.player())
    {
        return;
    }

    const GameScreenConfig &cfg = Context::gameScreenConfig();
    float y = cfg.skillButtonBottomSpacing();
    float x = viewportSize_[0] - cfg.skillButtonRightSpacing() -
              (skillButtons_.size() - 1) * cfg.skillButtonSpacing();

    for (auto &button : skillButtons_)
    {
        button.setPos(x, y);
        x += cfg.skillButtonSpacing();
    }
}

} // end of namespace botlib
} // end of namespace mcdane
