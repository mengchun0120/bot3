#ifndef INCLUDED_BOTLIB_SHOW_MAP_SCREEN_H
#define INCLUDED_BOTLIB_SHOW_MAP_SCREEN_H

#include <botlib_game_object_factory.h>
#include <botlib_game_map.h>
#ifdef __ANDROID__
#include <botlib_map_navigator.h>
#endif
#include <botlib_screen.h>

namespace mcdane {
namespace botlib {

class ShowMapScreen: public Screen {
public:
    ShowMapScreen() = default;

    ShowMapScreen(const commonlib::Vector2 &viewportSize,
                  AppActions actions,
                  ScreenType nextScreenType=ScreenType::NONE,
                  bool initMap=true);

    ~ShowMapScreen() override = default;

    inline GameMap &map();

    void init(const commonlib::Vector2 &viewportSize,
              AppActions actions,
              ScreenType nextScreenType=ScreenType::NONE,
              bool initMap=true);

    void update(float timeDelta) override;

    void present() override;

    bool processInput(const commonlib::InputEvent &e) override;

#ifdef DESKTOP_APP
    void processKey(const commonlib::KeyEvent &e);
#endif

    void onViewportChange(float width, float height) override;

    void move(int horizontalDirection, int verticalDirection);

    void backout();

private:
    void loadMap(const commonlib::Vector2 &viewportSize);

#ifdef __ANDROID__
    void initNavigator();

    void handlePointerDown(float x, float y);

    void handlePointerMove(float x, float y);

    void presentOverlay();
#endif

private:
    GameObjectFactory factory_;
    GameMap map_;
    ScreenType nextScreenType_;
    commonlib::Vector2 viewportSize_;
#ifdef __ANDROID__
    MapNavigator navigator_;
    commonlib::Vector2 overlayViewportOrigin_;
#endif
};

GameMap &ShowMapScreen::map()
{
    return map_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
