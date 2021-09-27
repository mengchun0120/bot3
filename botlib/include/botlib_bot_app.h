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
    static void initInstance(const std::string& configFile,
                             const std::string& appDir);

    static BotApp& getInstance()
    {
        return *k_botApp;
    }

    ~BotApp() override;

    void preProcess() override;

    void process() override;

    void postProcess() override;

    ScreenManager& screenManager()
    {
        return screenManager_;
    }

private:
    static std::shared_ptr<BotApp> k_botApp;

    BotApp(const std::string& configFile,
           const std::string& appDir);

    void init(const std::string& configFile,
              const std::string& appDir);

#ifdef DESKTOP_APP
    void initWindow();
#endif

    void setupOpenGL(const AppConfig& cfg);

    void setupActions();

    void setupScreen(const AppConfig& cfg);

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

