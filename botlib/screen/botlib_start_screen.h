#ifndef INCLUDED_BOTLIB_START_SCREEN_H
#define INCLUDED_BOTLIB_START_SCREEN_H

#include <commonlib_vector.h>
#include <botlib_widget_group.h>
#include <botlib_screen.h>

namespace mcdane {
namespace botlib {

class StartScreen: public Screen {
public:
    StartScreen(const commonlib::Vector2& viewportSize,
                const AppActions& actions);

    ~StartScreen() override;

    void update(float delta) override;

    void present() override;

#ifdef  DESKTOP_APP
    bool processInput(const commonlib::InputEvent &e) override;
#endif

private:
    void initWidgets(const commonlib::Vector2& viewportSize);

    void prepareShader(const commonlib::Vector2& viewportSize);

    void startGame();

    void showSettings();

    void exitGame();

#ifdef DESKTOP_APP
    bool processMouseButtonEvent(const commonlib::MouseButtonEvent& e);

    bool processMouseMoveEvent(const commonlib::MouseMoveEvent& e);

    bool processKeyEvent(const commonlib::KeyEvent& e);
#endif

private:
    WidgetGroup widgets_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif