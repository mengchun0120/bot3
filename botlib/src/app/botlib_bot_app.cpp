#include <iostream>
#include <commonlib_log.h>
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
    using namespace std::placeholders;

    cfg_.load(configFile, appDir);
#ifdef DESKTOP_APP
    setupWindow(cfg_.width(), cfg_.height(), cfg_.title());
    inputManager_.init(window(), viewportHeight(), cfg_.inputQueueCapacity());
#endif
    setupOpenGL();
    inputManager_.enable();
    screenManager_.init(Screen::SCREEN_START);
    inputProcessor_ = std::bind(&ScreenManager::processInput,
                                &screenManager_, _1);
}

void BotApp::setupOpenGL()
{
    simpleShader_.init(cfg_.simpleVertexShaderFile(),
                       cfg_.simpleFragShaderFile());

    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void BotApp::preProcess()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void BotApp::process()
{
    inputManager_.processInput(inputProcessor_);

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

