#ifndef INCLUDED_BOTLIB_GAME_SCREEN_H
#define INCLUDED_BOTLIB_GAME_SCREEN_H

#include <botlib_screen.h>

namespace mcdane {
namespace botlib {

class GameScreen: public Screen {
public:
    GameScreen(const commonlib::Vector2& viewportSize,
               const AppActions actions);

    ~GameScreen() override;

    void update() override;

    void present() override;

    bool processInput(const commonlib::InputEvent &e) override;

private:
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

