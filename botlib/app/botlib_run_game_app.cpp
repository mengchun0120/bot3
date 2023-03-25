#include <commonlib_log.h>
#include <botlib_app_config.h>
#include <botlib_context.h>
#include <rungame_app.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

RunGameApp::RunGameApp(const std::string& configFile,
                       const std::string& appDir,
                       const std::string& mapFile)
{
    AppConfig::init(configFile, appDir);
    const AppConfig& cfg = AppConfig::instance();
    init(cfg.width(), cfg.height(), cfg.title());
    Context::init(AppConfig::instance());
    setupGame(mapFile);
}

void RunGameApp::process()
{
    InputManager::getInstance().processInput(inputProcessor_);
    deltaSmoother_.update();

    if (running())
    {
        screen_.update(deltaSmoother_.curTimeDelta());
        screen_.present();
    }
}

void RunGameApp::setupGame(const std::string& mapFile)
{
    setupDeltaSmoother();
    setupScreen(mapFile);
    setupInput();
}

void RunGameApp::setupDeltaSmoother()
{
    const AppConfig& cfg = AppConfig::instance();

    deltaSmoother_.init(cfg.timeDeltaHistoryLen());
    deltaSmoother_.start();
}

void RunGameApp::setupScreen(const std::string& mapFile)
{
    AppActions actions;

    actions.exitAction_ = std::bind(&RunGameApp::exitApp, this);
    Context::gameScreenConfig().setMapFile(mapFile);
    screen_.init(viewportSize(), actions);
}

void RunGameApp::setupInput()
{
    using namespace std::placeholders;

    const AppConfig& cfg = AppConfig::instance();

    InputManager::initInstance(window(),
                               viewportHeight(),
                               cfg.inputQueueCapacity());

    inputProcessor_ = std::bind(&GameScreen::processInput,
                                &screen_,
                                _1);

    InputManager::getInstance().enable();
}

void RunGameApp::exitApp()
{
    setRunning(false);
}

} // end of namespace botlib
} // end of namespace mcdane

