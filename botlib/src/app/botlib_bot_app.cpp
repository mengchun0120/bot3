#include <iostream>
#include <functional>
#include <commonlib_log.h>
#include <botlib_app_config.h>
#include <botlib_graphics.h>
#include <botlib_button.h>
#include <botlib_start_screen.h>
#include <botlib_bot_app.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

std::shared_ptr<BotApp> BotApp::k_botApp;

void BotApp::initInstance(const std::string& configFile,
                          const std::string& appDir)
{
    if (!k_botApp)
    {
        k_botApp.reset(new BotApp(configFile, appDir));
    }
}

BotApp::BotApp(const std::string& configFile,
               const std::string& appDir)
    : App()
{
    init(configFile, appDir);
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
                  const std::string& appDir)
{
    AppConfig::initInstance(configFile, appDir);
    const AppConfig& cfg = AppConfig::getInstance();
#ifdef DESKTOP_APP
    setupWindow(cfg.width(), cfg.height(), cfg.title());
#endif
    setupOpenGL();
    setupScreen();
    setupInput();
}

void BotApp::setupOpenGL()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    const AppConfig& cfg = AppConfig::getInstance();
    Graphics::initInstance(cfg.simpleVertexShaderFile(),
                           cfg.simpleFragShaderFile(),
                           cfg.fontDir());
}

void setupWidget();

void BotApp::setupScreen()
{
    const AppConfig& cfg = AppConfig::getInstance();
    StartScreen::initConfig(cfg.startScreenConfigFile());

    screenManager_.init(Screen::SCREEN_START, viewportSize());
}

void BotApp::setupInput()
{
    using namespace std::placeholders;

    const AppConfig& cfg = AppConfig::getInstance();
    InputManager::initInstance(window(),
                               viewportHeight(),
                               cfg.inputQueueCapacity());

    inputProcessor_ = std::bind(&ScreenManager::processInput,
                                &screenManager_,
                                _1);
}

} // end of namespace botlib
} // end of namespace mcdane

