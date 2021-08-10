#include <commonlib_log.h>
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
    using namespace std::placeholders;

    cfg_.load(configFile);
#ifdef DESKTOP_APP
    initWindow();
#endif
    setupOpenGL();
    inputProcessor_ = std::bind(&processInput, this, _1);
    inputManager_.init(window(), viewportHeight_, cfg_.inputQueueCapacity());
    inputManager_.enable();
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
    inputManager_.processInput(inputProcessor_);

    return true;
}

bool BotApp::postProcess()
{
    return App::postProcess();
}

bool BotApp::processInput(const InputEvent& e)
{
    LOG_INFO << "processed event " << e << LOG_END;
    return true;
}

} // end of namespace commonlib
} // end of namespace mcdane

