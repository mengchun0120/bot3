#ifndef INCLUDED_BOTLIB_SHOWMAP_SCREEN_H
#define INCLUDED_BOTLIB_SHOWMAP_SCREEN_H

#include <botlib_game_map.h>
#include <botlib_screen.h>

namespace mcdane {
namespace botlib {

class ShowMapScreen: public Screen {
public:
    ShowMapScreen() = default;

    ShowMapScreen(const commonlib::Vector2& viewportSize,
                  AppActions actions,
                  ScreenType nextScreenType=ScreenType::NONE);

    ~ShowMapScreen() override = default;

    void init(const commonlib::Vector2& viewportSize,
              AppActions actions,
              ScreenType nextScreenType=ScreenType::NONE);

    void update(float timeDelta) override;

    void present() override;

    bool processInput(const commonlib::InputEvent& e) override;

private:
    void loadMap(const commonlib::Vector2& viewportSize);

    bool processKey(const commonlib::KeyEvent& e);

    bool processEscKey();

    bool processUpKey();

    bool processDownKey();

    bool processRightKey();

    bool processLeftKey();

private:
    GameMap map_;
    ScreenType nextScreenType_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif
