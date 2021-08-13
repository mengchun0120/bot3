#include <commonlib_log.h>
#include <botlib_bot_app.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

std::shared_ptr<BotApp> BotApp::k_botApp;

void BotApp::initInstance(const std::string& configFile)
{
    if (!k_botApp)
    {
        k_botApp.reset(new BotApp(configFile));
    }
}

BotApp::BotApp(const std::string& configFile)
    : App()
{
    init(configFile);
}

BotApp::~BotApp()
{
}

void BotApp::init(const std::string& configFile)
{
    using namespace std::placeholders;

    cfg_.load(configFile);
#ifdef DESKTOP_APP
    initWindow();
#endif
    setupOpenGL();
    inputManager_.init(window(), viewportHeight_, cfg_.inputQueueCapacity());
    inputManager_.enable();
    screenManager_.init(Screen::SCREEN_START);
    inputProcessor_ = std::bind(&ScreenManager::processInput,
                                &screenManager_, _1);
}

#ifdef DESKTOP_APP
void BotApp::initWindow()
{
    setupWindow(cfg_.width(), cfg_.height(), cfg_.title());

    int width, height;
    glfwGetFramebufferSize(window(), &width, &height);
    viewportWidth_ = static_cast<float>(width);
    viewportHeight_ = static_cast<float>(height);
}
#endif

void BotApp::setupOpenGL()
{
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

