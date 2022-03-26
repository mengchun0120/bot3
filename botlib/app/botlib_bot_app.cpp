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
               const std::string& appDir,
               const std::string& mapFile)
    : App()
{
    init(configFile, appDir, mapFile);
}

BotApp::~BotApp()
{
}

void BotApp::preProcess()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void BotApp::process()
{
    InputManager::getInstance().processInput(inputProcessor_);

    if (running())
    {
        screenManager_.update();
        screenManager_.present();
    }
}

void BotApp::postProcess()
{
    screenManager_.postProcess();
    App::postProcess();
}


void BotApp::init(const std::string& configFile,
                  const std::string& appDir,
                  const std::string& mapFile)
{
    AppConfig::init(configFile, appDir);
    const AppConfig& cfg = AppConfig::instance();
#ifdef DESKTOP_APP
    setupWindow(cfg.width(), cfg.height(), cfg.title());
#endif
    Context::init(cfg);
    setupOpenGL(cfg);
    setupWidget(cfg);
    setupActions();
    setupScreen(cfg.startScreenConfigFile(), mapFile);
    setupInput(cfg);
}

void BotApp::setupOpenGL(const AppConfig& cfg)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void BotApp::setupWidget(const AppConfig& cfg)
{
    Button::initConfig(cfg.buttonConfigFile(), cfg.picDir());
}

void BotApp::setupActions()
{
    using namespace std::placeholders;

    actions_.exitAction_ = std::bind(&BotApp::exitApp, this);
    actions_.switchAction_ = std::bind(&ScreenManager::switchScreen,
                                       &screenManager_, _1);
}


void BotApp::setupScreen(const std::string& startScreenCfgFile,
                         const std::string& mapFile)
{
    screenManager_.init(ScreenType::START,
                        viewportSize(),
                        actions_,
                        startScreenCfgFile,
                        mapFile);
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

