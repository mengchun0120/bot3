#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <botlib_app_config.h>
#include <botlib_context.h>
#include <botlib_show_map_app.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

ShowMapApp::ShowMapApp()
    : App()
{
}

ShowMapApp::~ShowMapApp()
{
}

#ifdef DESKTOP_APP
void ShowMapApp::init(const std::string &configFile,
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
void ShowMapApp::init(android_app *app,
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

void ShowMapApp::process()
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

bool ShowMapApp::operator()(const commonlib::InputEvent &e)
{
    if (!running())
    {
        return false;
    }

    screen_.processInput(e);
    return running();
}

void ShowMapApp::setupGame(const std::string &mapFile)
{
    setupDeltaSmoother();
    setupScreen(mapFile);
    setupInput();
}

void ShowMapApp::setupDeltaSmoother()
{
    const AppConfig &cfg = AppConfig::instance();
    deltaSmoother_.init(cfg.timeDeltaHistoryLen());
    deltaSmoother_.start();
}

void ShowMapApp::setupScreen(const std::string &mapFile)
{
    if (mapFile.empty())
    {
        THROW_EXCEPT(InvalidArgumentException, "mapFile is empty");
    }

    AppActions actions;

    actions.exitAction_ = std::bind(&ShowMapApp::exitApp, this);
    Context::showMapScreenConfig().setMapFile(mapFile);
    screen_.init(viewportSize(), actions);
}

#ifdef DESKTOP_APP
void ShowMapApp::setupInput()
{
    const AppConfig &cfg = AppConfig::instance();
    InputManager::initInstance(window(), viewportSize(),
                               cfg.inputQueueCapacity());
    InputManager::instance().enable();
}
#elif __ANDROID__
void ShowMapApp::setupInput()
{
    InputManager::initInstance(app_, viewportSize());
}
#endif

void ShowMapApp::onViewportChange(float width, float height)
{
    App::onViewportChange(width, height);
    InputManager::instance().setViewportSize(viewportSize());
    screen_.onViewportChange(viewportWidth(), viewportHeight());
}

void ShowMapApp::exitApp()
{
    setRunning(false);
}

} // end of namespace botlib
} // end of namespace mcdane

