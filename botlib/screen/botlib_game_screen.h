#ifndef INCLUDED_BOTLIB_GAME_SCREEN_H
#define INCLUDED_BOTLIB_GAME_SCREEN_H

#include <list>
#include <botlib_game_map.h>
#include <botlib_game_object_dumper.h>
#include <botlib_player.h>
#include <botlib_skill_with_cost.h>
#include <botlib_progress_bar.h>
#include <botlib_progress_pie.h>
#include <botlib_skill_button.h>
#include <botlib_game_navigator.h>
#include <botlib_message_box.h>
#include <botlib_icon.h>
#include <botlib_update_context.h>
#include <botlib_game_obj_flag_resetter.h>
#include <botlib_game_obj_updater.h>
#include <botlib_screen.h>

namespace mcdane {
namespace botlib {

class GameScreen: public Screen {
public:
    GameScreen() = default;

    ~GameScreen() override = default;

    void init(const commonlib::Vector2 &viewportSize,
              const AppActions actions,
              ScreenType nextScreenType=ScreenType::NONE,
              bool exerciseMode=false);

    void update(float timeDelta) override;

    void present() override;

    bool processInput(const commonlib::InputEvent &e) override;

    void onViewportChange(float width, float height) override;

private:
    void loadMap(const commonlib::Vector2 &viewportSize,
                 const std::string &mapFile);

    void initMapAccessors();

    void initPlayerGoodieFunc();

    void initProgressBar();

    void initMessageBox();

    void initGoodiePies();

    void calculateGoodiePiePos();

    void createGoodiePies();

    inline ProgressPie &getGoodiePie(const GoodieEffect &e);

    void initAIRobotCount();

    void initSkillButtons();

    bool addSkillButton(Skill *skill,
                        float x,
                        float y);

    bool processInputEndGame(const commonlib::InputEvent &e);

    bool processInputGame(const commonlib::InputEvent &e);

#ifdef DESKTOP_APP
    bool processMouseButton(const commonlib::MouseButtonEvent &e);

    bool processMouseMove(const commonlib::MouseMoveEvent &e);

    bool processKey(const commonlib::KeyEvent &e);

    void enableSkillForInput(int input);

#elif __ANDROID__
    bool onSkillButtonPressed(float x, float y);
#endif

    void onPointerDown(float x, float y);

    void preUpdate(float timeDelta);

    void updateObjs();

    void updatePlayer();

    void clearUpdateFlags();

    void updateNonPlayerObjects();

    void updateOverlay();

    void updateProgressBar();

    void updateGoodiePieRatio();

    void updateGoodiePiePos();

    void updateSkillButtons();

    void clearObjs();

    void clearObjectsFromMoveOutRegion(int moveOutRegionCount);

    void showMsg();

    void showVictory();

    void showFail();

    inline bool isPlayerAvailable();

    void presentOverlay();

    void presentGoodiePies();

    void presentSkillButtons();

    void resetOverlayPos();

    void resetMessageBoxPos();

    void resetProgressBarPos();

    void resetGoodiePiePos();

    void resetAIRobotCountPos();

    void resetSkillButtonPos();

private:
    bool exerciseMode_;
    ScreenType nextScreenType_;
    UpdateContext cxt_;
    GameMap map_;
    commonlib::Vector2 viewportSize_;
    commonlib::Vector2 overlayViewportOrigin_;
    GameObjFlagResetter flagResetter_;
    GameObjUpdater objUpdater_;
    ProgressBar armorProgressBar_;
    ProgressBar energyProgressBar_;
    MessageBox msgBox_;
    commonlib::Vector2 aiRobotIconPos_;
    Icon aiRobotCountIcon_;
    commonlib::Vector2 aiRobotCountPos_;
    std::string aiRobotCountStr_;
    commonlib::Region<int> prevArea_;
    std::vector<commonlib::Region<int>> moveOutRegions_;
    std::vector<commonlib::Vector2> goodiePiePos_;
    std::vector<ProgressPie> goodiePies_;
    std::list<SkillButton> skillButtons_;
};

ProgressPie &GameScreen::getGoodiePie(const GoodieEffect &e)
{
    return goodiePies_[lastingGoodieTypeIndex(e.type())];
}

bool GameScreen::isPlayerAvailable()
{
    return map_.player() &&
           map_.player()->state() == GameObjectState::ALIVE;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
