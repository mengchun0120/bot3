#ifndef INCLUDED_ITEST_TEST_GAME_SCREEN_APP_H
#define INCLUDED_ITEST_TEST_GAME_SCREEN_APP_H

#include <commonlib_app.h>
#include <commonlib_input_manager.h>
#include <botlib_time_delta_smoother.h>
#include <botlib_game_screen.h>

namespace mcdane {
namespace itest {

class TestGameScreenApp: public commonlib::App {
public:
    TestGameScreenApp(const std::string& configFile,
                      const std::string& appDir);

    ~TestGameScreenApp() = default;

    void preProcess() override;

    void process() override;

    void postProcess() override;

private:
    void setupWindow();

    void setupOpenGL();

    void setupActions();

    void setupGame();

    void setupScreen();

    void setupInput();

    void exitApp();

    void switchScreen(botlib::ScreenType screenType);

private:
    botlib::AppActions actions_;
    botlib::TimeDeltaSmoother deltaSmoother_;
    commonlib::InputProcessor inputProcessor_;
    botlib::GameScreen screen_;
};

} // end of namespace itest
} // end of namespace mcdane

#endif

