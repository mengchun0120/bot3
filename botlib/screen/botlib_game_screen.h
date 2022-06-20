#ifndef INCLUDED_BOTLIB_GAME_SCREEN_H
#define INCLUDED_BOTLIB_GAME_SCREEN_H

#include <botlib_game_map.h>
#include <botlib_game_object_dumper.h>
#include <botlib_player.h>
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

    void update(float timeDelta) override;

    void present() override;

    bool processInput(const commonlib::InputEvent& e) override;

private:
    void loadMap(const commonlib::Vector2& viewportSize,
                 const std::string& mapFile);

    bool processMouseButton(const commonlib::MouseButtonEvent& e);

    bool processMouseMove(const commonlib::MouseMoveEvent& e);

    bool processKey(const commonlib::KeyEvent& e);

    void processFireKey(const commonlib::KeyEvent& e);

    void processForwardKey(const commonlib::KeyEvent& e);

    void updatePlayer(float timeDelta);

    void clearMapUpdated();

    void updateObjects(float timeDelta);

    inline bool isPlayerAvailable();

private:
    GameMap map_;
    GameObjectDumper objDumper_;
};

bool GameScreen::isPlayerAvailable()
{
    return map_.player() &&
           map_.player()->state() == GameObjectState::ALIVE;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

