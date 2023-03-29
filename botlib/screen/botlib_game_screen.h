#ifndef INCLUDED_BOTLIB_GAME_SCREEN_H
#define INCLUDED_BOTLIB_GAME_SCREEN_H

#include <botlib_game_map.h>
#include <botlib_game_object_dumper.h>
#include <botlib_player.h>
#include <botlib_progress_bar.h>
#include <botlib_progress_pie.h>
#include <botlib_message_box.h>
#include <botlib_game_navigator.h>
#include <botlib_icon.h>
#include <botlib_update_context.h>
#include <botlib_screen.h>

namespace mcdane {
namespace botlib {

class GameScreen: public Screen {
public:
    GameScreen() = default;

    GameScreen(const commonlib::Vector2 &viewportSize,
               const AppActions actions,
               ScreenType nextScreenType=ScreenType::NONE);

    ~GameScreen() override = default;

    void init(const commonlib::Vector2 &viewportSize,
              const AppActions actions,
              ScreenType nextScreenType=ScreenType::NONE);

    void update(float timeDelta) override;

    void present() override;

    bool processInput(const commonlib::InputEvent &e) override;

    void onViewportChange(float width, float height) override;

private:
    void loadMap(const commonlib::Vector2 &viewportSize,
                 const std::string &mapFile);

    void initProgressBar();

    void initMessageBox();

    void initAIRobotCount();

    void initGoodiePies();

    void initGoodiePiePos();

    void initSkillButtons();

    void createGoodiePies();

    bool processInputEndGame(const commonlib::InputEvent &e);

    bool processInputGame(const commonlib::InputEvent &e);

#ifdef DESKTOP_APP
    bool processMouseButton(const commonlib::MouseButtonEvent &e);

    bool processMouseMove(const commonlib::MouseMoveEvent &e);

    bool processKey(const commonlib::KeyEvent &e);

    void enableSkillForInput(int input);

#elif __ANDROID__
    void initGameNavigator();

    void onSteer(const Vector2 &direction);

    void onToggle(bool greenOrRed);

    void onSkillButtonPressed(float x, float y);
#endif

    void updatePlayer();

    void clearUpdateFlags();

    void updateNonPlayerObjects();

    void updateProgressBar();

    inline bool isPlayerAvailable();

    void presentOverlay();

    void presentGoodiePies();

    void presentSkillButtons();

    void showVictory();

    void showFail();

    void clearObjectsFromMoveOutRegion(int moveOutRegionCount);

    int skillPieCount();

    float skillPieRadius();

private:
    ScreenType nextScreenType_;
    UpdateContext cxt_;
    GameMap map_;
    commonlib::Vector2 viewportSize_;
    commonlib::Vector2 overlayViewportOrigin_;
    ProgressBar armorProgressBar_;
    ProgressBar energyProgressBar_;
    MessageBox msgBox_;
    commonlib::Vector2 aiRobotIconPos_;
    Icon aiRobotCountIcon_;
    commonlib::Vector2 aiRobotCountPos_;
    std::string aiRobotCountStr_;
    std::vector<commonlib::Region<int>> moveOutRegions_;
    std::vector<commonlib::Vector2> goodiePiePos_;
    std::vector<ProgressPie> goodiePies_;
    GameNavigator navigator_;
};

bool GameScreen::isPlayerAvailable()
{
    return map_.player() &&
           map_.player()->state() == GameObjectState::ALIVE;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
