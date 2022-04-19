#ifndef INCLUDED_BOTLIB_GAME_SCREEN_H
#define INCLUDED_BOTLIB_GAME_SCREEN_H

#include <botlib_game_map.h>
#include <botlib_game_object_flag_resetter.h>
#include <botlib_game_object_updater.h>
#include <botlib_screen.h>

namespace mcdane {
namespace botlib {

class GameScreen: public Screen {
public:
    GameScreen() = default;

    GameScreen(const commonlib::Vector2& viewportSize,
               const AppActions actions);

    ~GameScreen() override;

    void init(const commonlib::Vector2& viewportSize,
              const AppActions actions);

    void update(float delta) override;

    void present() override;

    bool processInput(const commonlib::InputEvent& e) override;

private:
    void loadMap(const commonlib::Vector2& viewportSize);

    bool processMouseButton(const commonlib::MouseButtonEvent& e);

    bool processMouseMove(const commonlib::MouseMoveEvent& e);

    bool processKey(const commonlib::KeyEvent& e);

    void updatePlayer(float delta);

    void clearMapUpdated();

    void updateObjects(float delta);

private:
    GameMap map_;
    GameObjectFlagResetter objFlagResetter_;
    GameObjectUpdater objUpdater_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

