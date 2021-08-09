#include <commonlib_bot_app.h>

namespace mcdane {
namespace commonlib {

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
    cfg_.load(configFile);
#ifdef DESKTOP_APP
    initWindow();
#endif
    inputManager_.init(window(), viewportHeight_, cfg_.inputQueueCapacity());
    setupOpenGL();
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

bool BotApp::preProcess()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    return true;
}

bool BotApp::process()
{
    return true;
}

bool BotApp::postProcess()
{
    return App::postProcess();
}

} // end of namespace commonlib
} // end of namespace mcdane

