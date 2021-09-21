#ifndef INCLUDED_BOTLIB_START_SCREEN_H
#define INCLUDED_BOTLIB_START_SCREEN_H

#include <string>
#include <botlib_widget_group.h>
#include <botlib_screen.h>

namespace mcdane {
namespace botlib {

class StartScreen: public Screen {
public:
    static void initConfig(const std::string& configFile);

    StartScreen();

    ~StartScreen() override;

    void update() override;

    void present() override;

    bool processInput(const commonlib::InputEvent &e) override;

private:
    void initWidgets();

    void prepareShader();

    void startGame();

    void showSettings();

    void exitGame();

#ifdef DESKTOP_APP
    bool processMouseButtonEvent(const commonlib::MouseButtonEvent& e);

    bool processMouseMoveEvent(const commonlib::MouseMoveEvent& e);

    bool processKeyEvent(const commonlib::KeyEvent& e);
#endif

private:
    static float k_buttonWidth;
    static float k_buttonHeight;
    static float k_buttonSpacing;

    WidgetGroup widgets_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

