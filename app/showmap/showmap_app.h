#ifndef INCLUDED_SHOWMAP_APP_H
#define INCLUDED_SHOWMAP_APP_H

#include <commonlib_app.h>
#include <commonlib_input_manager.h>
#include <botlib_time_delta_smoother.h>
#include <botlib_screen_manager.h>
#include <botlib_input_manager.h>
#include <botlib_app_actions.h>

namespace mcdane {
namespace showmap {

class ShowMapApp: commonlib::App {
public:
    BotApp(const std::string& configFile,
           const std::string& mapFile,
           const std::string& appDir);

    ~BotApp() override;

    void process() override;

private:
    void init(const std::string& configFile,
              const std::string& appDir);

    void setupOpenGL();

    void setupGame();

    void setupDeltaSmoother();

    void setupActions();

    void setupScreen();

    void setupInput();

    void exitApp();

private:
    botlib::TimeDeltaSmoother deltaSmoother_;
    botlib::ScreenManager screenManager_;
    commonlib::InputProcessor inputProcessor_;
    botlib::AppActions actions_;
};

} // end of namespace showmap
} // end of namespace mcdane

#endif
