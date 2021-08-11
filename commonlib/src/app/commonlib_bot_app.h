#ifndef INCLUDED_COMMONLIB_BOT_APP_H
#define INCLUDED_COMMONLIB_BOT_APP_H

#include <commonlib_app.h>
#include <commonlib_app_config.h>
#include <commonlib_input_manager.h>
#include <commonlib_screen_manager.h>

namespace mcdane {
namespace commonlib {

class BotApp: public App {
public:
    static void initInstance(const std::string& configFile);

    static BotApp& getInstance()
    {
        return *k_botApp;
    }

    ~BotApp() override;

    void preProcess() override;

    void process() override;

    void postProcess() override;

    const AppConfig& config() const
    {
        return cfg_;
    }

    ScreenManager& screenManager()
    {
        return screenManager_;
    }

private:
    static std::shared_ptr<BotApp> k_botApp;

    BotApp(const std::string& configFile);

    void init(const std::string& configFile);

#ifdef DESKTOP_APP
    void initWindow();
#endif

    void setupOpenGL();

private:
    AppConfig cfg_;
    float viewportWidth_;
    float viewportHeight_;
    InputManager inputManager_;
    InputProcessor inputProcessor_;
    ScreenManager screenManager_;
};

} // end of namespace commonlib
} // end of namespace mcdane

#endif

