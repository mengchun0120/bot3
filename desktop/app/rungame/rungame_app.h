#ifndef INCLUDED_ITEST_TEST_GAME_SCREEN_APP_H
#define INCLUDED_ITEST_TEST_GAME_SCREEN_APP_H

#include <commonlib_app.h>
#include <commonlib_input_manager.h>
#include <botlib_time_delta_smoother.h>
#include <botlib_game_screen.h>

namespace mcdane {
namespace rungame {

class RunGameApp: public commonlib::App {
public:
    RunGameApp(const std::string& configFile,
               const std::string& appDir,
               const std::string& mapFile);

    ~RunGameApp() = default;

    void process() override;

private:
    void setupGame(const std::string& mapFile);

    void setupDeltaSmoother();

    void setupScreen(const std::string& mapFile);

    void setupInput();

    void exitApp();

private:
    botlib::TimeDeltaSmoother deltaSmoother_;
    commonlib::InputProcessor inputProcessor_;
    botlib::GameScreen screen_;
};

} // end of namespace rungame
} // end of namespace mcdane

#endif

