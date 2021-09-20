#include <iostream>
#include <commonlib_log.h>
#include <botlib_app_config.h>
#include <botlib_graphics.h>
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

void BotApp::init(const std::string& configFile,
                  const std::string& appDir)
{
    AppConfig::initInstance(configFile, appDir);
    const AppConfig& cfg = AppConfig::getInstance();
#ifdef DESKTOP_APP
    setupWindow(cfg.width(), cfg.height(), cfg.title());
#endif
    setupOpenGL();
    screenManager_.init(Screen::SCREEN_START);
}

void BotApp::setupOpenGL()
{
    const AppConfig& cfg = AppConfig::getInstance();
    Graphics::initInstance(cfg.simpleVertexShaderFile(),
                           cfg.simpleFragShaderFile(),
                           cfg.fontDir());

    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void BotApp::preProcess()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void BotApp::process()
{
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

} // end of namespace botlib
} // end of namespace mcdane

