#ifndef INCLUDED_BOTLIB_GAME_SCREEN_H
#define INCLUDED_BOTLIB_GAME_SCREEN_H

#include <commonlib_vector.h>
#include <botlib_screen.h>

namespace mcdane {
namespace botlib {

class GameScreenConfig;

class GameScreen: public Screen {
public:
    GameScreen(const commonlib::Vector2& viewportSize,
               const AppActions actions,
               const GameScreenConfig* cfg);

    ~GameScreen() override;

    void update() override;

    void present() override;

    bool processInput(const commonlib::InputEvent& e) override;

private:
    bool processMouseButton(const commonlib::MouseButtonEvent& e);

    bool processMouseMove(const commonlib::MouseMoveEvent& e);

    bool processKey(const commonlib::KeyEvent& e);

private:
    const GameScreenConfig* cfg_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

