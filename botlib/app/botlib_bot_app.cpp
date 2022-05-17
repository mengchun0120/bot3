#include <iostream>
#include <commonlib_log.h>
#include <botlib_app_config.h>
#include <botlib_context.h>
#include <botlib_button.h>
#include <botlib_start_screen.h>
#include <botlib_bot_app.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

BotApp::BotApp(const std::string& configFile,
               const std::string& appDir)
    : App()
{
    init(configFile, appDir);
}

BotApp::~BotApp()
{
}

void BotApp::process()
{
    InputManager::getInstance().processInput(inputProcessor_);

    if (running())
    {
        screenManager_.update(deltaSmoother_.curTimeDelta());
        screenManager_.present();
    }

    screenManager_.postProcess();
    postProcess();
}

void BotApp::init(const std::string& configFile,
                  const std::string& appDir)
{
    AppConfig::init(configFile, appDir);
    const AppConfig& cfg = AppConfig::instance();
#ifdef DESKTOP_APP
    setupWindow(cfg.width(), cfg.height(), cfg.title());
#endif
    Context::init(cfg);
    setupOpenGL(cfg);
    setupGame(cfg);
}

void BotApp::setupOpenGL(const AppConfig& cfg)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void BotApp::setupGame(const AppConfig& cfg)
{
    setupDeltaSmoother(cfg);
    setupActions();
    setupScreen();
    setupInput(cfg);
}

void BotApp::setupDeltaSmoother(const AppConfig& cfg)
{
    deltaSmoother_.init(cfg.timeDeltaHistoryLen());
    deltaSmoother_.start();
}

void BotApp::setupActions()
{
    using namespace std::placeholders;

    actions_.exitAction_ = std::bind(&BotApp::exitApp, this);
    actions_.switchAction_ = std::bind(&ScreenManager::switchScreen,
                                       &screenManager_, _1);
}

void BotApp::setupScreen()
{
    screenManager_.init(ScreenType::START,
                        viewportSize(),
                        actions_);
}

void BotApp::setupInput(const AppConfig& cfg)
{
    using namespace std::placeholders;

    InputManager::initInstance(window(),
                               viewportHeight(),
                               cfg.inputQueueCapacity());

    inputProcessor_ = std::bind(&ScreenManager::processInput,
                                &screenManager_,
                                _1);

    InputManager::getInstance().enable();
}

void BotApp::exitApp()
{
    setRunning(false);
}

} // end of namespace botlib
} // end of namespace mcdane

