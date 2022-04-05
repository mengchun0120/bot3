#include <botlib_app_config.h>
#include <botlib_context.h>
#include <botlib_button.h>
#include <botlib_hp_indicator.h>
#include <itest_test_game_screen_app.h>

using namespace mcdane::commonlib;
using namespace mcdane::botlib;

namespace mcdane {
namespace itest {

TestGameScreenApp::TestGameScreenApp(const std::string& configFile,
                                     const std::string& appDir)
{
    AppConfig::init(configFile, appDir);
    setupWindow();
    Context::init(AppConfig::instance());
    setupOpenGL();
    setupActions();
    setupGame();
    setupScreen();
    setupInput();
}

void TestGameScreenApp::preProcess()
{
    glClear(GL_COLOR_BUFFER_BIT);
    deltaSmoother_.updateTimeDelta();
}

void TestGameScreenApp::process()
{
    InputManager::getInstance().processInput(inputProcessor_);

    if (running())
    {
        screen_.update();
        screen_.present();
    }
}

void TestGameScreenApp::postProcess()
{
    App::postProcess();
}

void TestGameScreenApp::setupWindow()
{
    const AppConfig& cfg = AppConfig::instance();

    App::setupWindow(cfg.width(), cfg.height(), cfg.title());
}

void TestGameScreenApp::setupOpenGL()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void TestGameScreenApp::setupActions()
{
    using namespace std::placeholders;

    actions_.exitAction_ = std::bind(&TestGameScreenApp::exitApp, this);
    actions_.switchAction_ = std::bind(&TestGameScreenApp::switchScreen,
                                       this,
                                       _1);
}

void TestGameScreenApp::setupGame()
{
    const AppConfig& cfg = AppConfig::instance();

    deltaSmoother_.init(cfg.timeDeltaHistoryLen());
    deltaSmoother_.start();
}

void TestGameScreenApp::setupScreen()
{
    screen_.init(viewportSize(), actions_);
}

void TestGameScreenApp::setupInput()
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

void TestGameScreenApp::exitApp()
{
    setRunning(false);
}

void TestGameScreenApp::switchScreen(botlib::ScreenType screenType)
{
}

} // end of namespace itest
} // end of namespace mcdane

