#include <botlib_app_config.h>
#include <botlib_context.h>
#include <showmap_app.h>

using namespace mcdane::commonlib;
using namespace mcdane::botlib;

namespace mcdane {
namespace showmap {

ShowMapApp::ShowMapApp(const std::string& configFile,
                       const std::string& appDir,
                       const std::string& mapFile)
{
    init(configFile, appDir, mapFile);
}

ShowMapApp::~ShowMapApp()
{
}

void ShowMapApp::process()
{
    InputManager::getInstance().processInput(inputProcessor_);

    if (running())
    {
        screen_.update(deltaSmoother_.curTimeDelta());
        screen_.present();
    }

    postProcess();
}

void ShowMapApp::init(const std::string& configFile,
                      const std::string& appDir,
                      const std::string& mapFile)
{
    AppConfig::init(configFile, appDir);
    const AppConfig& cfg = AppConfig::instance();
#ifdef DESKTOP_APP
    setupWindow(cfg.width(), cfg.height(), cfg.title());
#endif
    Context::init(cfg);
    setupOpenGL();
    setupGame(mapFile);
}

void ShowMapApp::setupOpenGL()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void ShowMapApp::setupGame(const std::string& mapFile)
{
    setupDeltaSmoother();
    setupScreen(mapFile);
    setupInput();
}

void ShowMapApp::setupDeltaSmoother()
{
    const AppConfig& cfg = AppConfig::instance();
    deltaSmoother_.init(cfg.timeDeltaHistoryLen());
    deltaSmoother_.start();
}

void ShowMapApp::setupScreen(const std::string& mapFile)
{
    AppActions actions;

    actions.exitAction_ = std::bind(&ShowMapApp::exitApp, this);
    Context::showMapScreenConfig().setMapFile(mapFile);
    screen_.init(viewportSize(), actions);
}

void ShowMapApp::setupInput()
{
    using namespace std::placeholders;

    const AppConfig& cfg = AppConfig::instance();

    InputManager::initInstance(window(),
                               viewportHeight(),
                               cfg.inputQueueCapacity());

    inputProcessor_ = std::bind(&ShowMapScreen::processInput,
                                &screen_,
                                _1);

    InputManager::getInstance().enable();
}

void ShowMapApp::exitApp()
{
    setRunning(false);
}

} // end of namespace showmap
} // end of namespace mcdane

