#include <commonlib_log.h>
#include <commonlib_input_manager.h>
#include <botlib_app_config.h>
#include <botlib_context.h>
#include <botlib_run_game_app.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

#ifdef DESKTOP_APP
void RunGameApp::init(const std::string &configFile,
                      const std::string &appDir,
                      const std::string &mapFile)
{
    AppConfig::init(configFile, appDir);
    const AppConfig &cfg = AppConfig::instance();
    App::init(cfg.width(), cfg.height(), cfg.title());
    Context::init(cfg);
    setupGame(mapFile);
}
#elif __ANDROID__
void RunGameApp::init(android_app *app,
                      const std::string &configFile,
                      const std::string &mapFile)
{
    AppConfig::init(configFile);
    App::init(app);
    const AppConfig &cfg = AppConfig::instance();
    Context::init(cfg);
    setupGame(mapFile);
}
#endif

void RunGameApp::process()
{
    App::process();

    InputManager::instance().processInput(*this);
    deltaSmoother_.update();

    if (running())
    {
        screen_.update(deltaSmoother_.curTimeDelta());
        screen_.present();
    }

    postProcess();
}

bool RunGameApp::operator()(const commonlib::InputEvent &e)
{
    if (!running())
    {
        return false;
    }

    screen_.processInput(e);
    return running();
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

#ifdef DESKTOP_APP
void RunGameApp::setupInput()
{
    const AppConfig &cfg = AppConfig::instance();
    InputManager::initInstance(window(), viewportSize(),
                               cfg.inputQueueCapacity());
    InputManager::instance().enable();
}
#elif __ANDROID__
void RunGameApp::setupInput()
{
    InputManager::initInstance(app_, viewportSize());
}
#endif

void RunGameApp::onViewportChange(float width, float height)
{
    App::onViewportChange(width, height);
    InputManager::instance().setViewportSize(viewportSize());
    screen_.onViewportChange(viewportWidth(), viewportHeight());
}

void RunGameApp::exitApp()
{
    setRunning(false);
}

} // end of namespace botlib
} // end of namespace mcdane

