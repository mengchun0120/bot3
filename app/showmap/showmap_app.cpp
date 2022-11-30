#include <showmap_app.h>

namespace mcdane {
namespace showmap {

BotApp::BotApp(const std::string& configFile,
               const std::string& mapFile,
               const std::string& appDir)
{
    init(configFile, appDir);
}

BotApp::~BotApp() override
{
}

void BotApp::process() override
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

void BotApp::setupOpenGL()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void BotApp::setupGame()
{
    setupDeltaSmoother();
    setupActions();
    setupScreen();
    setupInput();
}

void BotApp::setupDeltaSmoother()
{
    const AppConfig& cfg = AppConfig::instance();
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
}

void BotApp::setupInput()
{
    using namespace std::placeholders;

    const AppConfig& cfg = AppConfig::instance();

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

} // end of namespace showmap
} // end of namespace mcdane

