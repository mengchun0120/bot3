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
                  const AppActions actions,
                  const std::string& mapFile);

    ~ShowMapScreen() override = default;

    void init(const commonlib::Vector2& viewportSize,
              const AppActions actions,
              const std::string& mapFile);

    void update(float timeDelta) override;

    void present() override;

    bool processInput(const commonlib::InputEvent& e) override;

private:
    void loadMap(const commonlib::Vector2& viewportSize,
                 const std::string& mapFile);

    bool processKey(const commonlib::KeyEvent& e);

    bool processUpKey();

    bool processDownKey();

    bool processRightKey();

    bool processLeftKey();

private:
    static constexpr float k_deltaPerStroke = 20.0f;
    GameMap map_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif