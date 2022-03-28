#ifndef INCLUDED_BOTLIB_BOT_APP_H
#define INCLUDED_BOTLIB_BOT_APP_H

#include <commonlib_app.h>
#include <commonlib_input_manager.h>
#include <botlib_screen_manager.h>
#include <botlib_app_actions.h>

namespace mcdane {
namespace botlib {

class BotApp: public commonlib::App {
public:
    BotApp(const std::string& configFile,
           const std::string& appDir,
           const std::string& mapFile);

    ~BotApp() override;

    void preProcess() override;

    void process() override;

    void postProcess() override;

    ScreenManager& screenManager()
    {
        return screenManager_;
    }

private:
    void init(const std::string& configFile,
              const std::string& appDir,
              const std::string& mapFile);

#ifdef DESKTOP_APP
    void initWindow();
#endif

    void setupOpenGL(const AppConfig& cfg);

    void setupActions();

    void setupScreen(const std::string& mapFile);

    void setupInput(const AppConfig& cfg);

    void exitApp();

private:
    ScreenManager screenManager_;
    commonlib::InputProcessor inputProcessor_;
    AppActions actions_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

