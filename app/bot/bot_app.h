#ifndef INCLUDED_BOT_APP_H
#define INCLUDED_BOT_APP_H

#include <commonlib_app.h>
#include <commonlib_input_manager.h>
#include <botlib_time_delta_smoother.h>
#include <botlib_screen_manager.h>
#include <botlib_app_config.h>
#include <botlib_app_actions.h>

namespace mcdane {
namespace bot {

class BotApp: public commonlib::App {
public:
    BotApp(const std::string& configFile,
           const std::string& appDir);

    ~BotApp() override;

    void process() override;

    botlib::ScreenManager& screenManager()
    {
        return screenManager_;
    }

private:
    void init(const std::string& configFile,
              const std::string& appDir);

#ifdef DESKTOP_APP
    void initWindow();
#endif

    void setupOpenGL(const botlib::AppConfig& cfg);

    void setupGame(const botlib::AppConfig& cfg);

    void setupDeltaSmoother(const botlib::AppConfig& cfg);

    void setupActions();

    void setupScreen();

    void setupInput(const botlib::AppConfig& cfg);

    void exitApp();

private:
    botlib::TimeDeltaSmoother deltaSmoother_;
    botlib::ScreenManager screenManager_;
    commonlib::InputProcessor inputProcessor_;
    botlib::AppActions actions_;
};

} // end of namespace bot
} // end of namespace mcdane

#endif

