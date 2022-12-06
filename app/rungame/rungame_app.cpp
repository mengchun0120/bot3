#include <botlib_app_config.h>
#include <botlib_context.h>
#include <rungame_app.h>

using namespace mcdane::commonlib;
using namespace mcdane::botlib;

namespace mcdane {
namespace rungame {

RunGameApp::RunGameApp(const std::string& configFile,
                       const std::string& appDir,
                       const std::string& mapFile)
{
    AppConfig::init(configFile, appDir);
    setupWindow();
    Context::init(AppConfig::instance());
    setupOpenGL();
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

    postProcess();
}

void RunGameApp::setupWindow()
{
    const AppConfig& cfg = AppConfig::instance();

    App::setupWindow(cfg.width(), cfg.height(), cfg.title());
}

void RunGameApp::setupOpenGL()
{
    glEnable(GL_BLEND);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
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

} // end of namespace rungame
} // end of namespace mcdane

