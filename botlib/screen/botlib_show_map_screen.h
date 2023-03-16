#ifndef INCLUDED_BOTLIB_SHOW_MAP_SCREEN_H
#define INCLUDED_BOTLIB_SHOW_MAP_SCREEN_H

#include <botlib_game_object_factory.h>
#include <botlib_game_map.h>
#include <botlib_screen.h>

namespace mcdane {
namespace botlib {

class ShowMapScreen: public Screen {
public:
    ShowMapScreen() = default;

    ShowMapScreen(const commonlib::Vector2& viewportSize,
                  AppActions actions,
                  ScreenType nextScreenType=ScreenType::NONE,
                  bool initMap=true);

    ~ShowMapScreen() override = default;

    GameMap& map()
    {
        return map_;
    }

    void init(const commonlib::Vector2& viewportSize,
              AppActions actions,
              ScreenType nextScreenType=ScreenType::NONE,
              bool initMap=true);

    void update(float timeDelta) override;

    void present() override;

#ifdef DESKTOP_APP
    bool processInput(const commonlib::InputEvent& e) override;

    bool processKey(const commonlib::KeyEvent& e);

    bool processEscKey();

    bool processUpKey();

    bool processDownKey();

    bool processRightKey();

    bool processLeftKey();
#endif

private:
    void loadMap(const commonlib::Vector2& viewportSize);

private:
    GameObjectFactory factory_;
    GameMap map_;
    ScreenType nextScreenType_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif
