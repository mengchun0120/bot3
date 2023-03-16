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
void ShowMapApp::init(android_app *app)
{
    AppConfig::init("config/bot_config_android.json");
    App::init(app);
    const AppConfig &cfg = AppConfig::instance();
    Context::init(cfg);
    setupGame("map_05.json");
}
#endif

void ShowMapApp::process()
{
    App::process();

    InputManager::instance().processInput(*this);

    if (running())
    {
        screen_.update(deltaSmoother_.curTimeDelta());
        screen_.present();
    }

    postProcess();
}

bool ShowMapApp::operator()(const commonlib::InputEvent &e)
{
    screen_.processInput(e);
    return true;
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
    screen_.onViewportChange(width, height);
}

void ShowMapApp::exitApp()
{
    setRunning(false);
}

} // end of namespace botlib
} // end of namespace mcdane

