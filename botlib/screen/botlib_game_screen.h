#ifndef INCLUDED_BOTLIB_GAME_SCREEN_H
#define INCLUDED_BOTLIB_GAME_SCREEN_H

#include <commonlib_vector.h>
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

    void update() override;

    void present() override;

    bool processInput(const commonlib::InputEvent& e) override;

private:
    bool processMouseButton(const commonlib::MouseButtonEvent& e);

    bool processMouseMove(const commonlib::MouseMoveEvent& e);

    bool processKey(const commonlib::KeyEvent& e);
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

