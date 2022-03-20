#include <botlib_app_config.h>
#include <botlib_game_lib.h>
#include <botlib_graphics.h>
#include <botlib_button.h>
#include <botlib_hp_indicator.h>
#include <itest_test_game_screen_app.h>

using namespace mcdane::commonlib;
using namespace mcdane::botlib;

namespace mcdane {
namespace itest {

TestGameScreenApp::TestGameScreenApp(const std::string& configFile,
                                     const std::string& appDir,
                                     const std::string& mapFile)
{
    setupAppConfig(configFile, appDir);
    setupWindow();
    setupOpenGL();
    setupWidget();
    setupActions();
    setupGame();
    setupScreen(mapFile);
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

void TestGameScreenApp::setupAppConfig(const std::string& configFile,
                                       const std::string& appDir)
{
    AppConfig::initInstance(configFile, appDir);
}

void TestGameScreenApp::setupWindow()
{
    const AppConfig& cfg = AppConfig::getInstance();

    App::setupWindow(cfg.width(), cfg.height(), cfg.title());
}

void TestGameScreenApp::setupOpenGL()
{
    const AppConfig& cfg = AppConfig::getInstance();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    Graphics::initInstance(cfg);
}

void TestGameScreenApp::setupWidget()
{
    const AppConfig& cfg = AppConfig::getInstance();

    Button::initConfig(cfg.buttonConfigFile(), cfg.picDir());
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
    const AppConfig& cfg = AppConfig::getInstance();

    GameLib::initInstance(cfg);

    HPIndicator::initConfig(cfg.hpIndicatorConfigFile());

    deltaSmoother_.init(cfg.timeDeltaHistoryLen());
    deltaSmoother_.start();
}

void TestGameScreenApp::setupScreen(const std::string& mapFile)
{
    GameScreenConfig cfg;

    cfg.init(mapFile);
    screen_.init(viewportSize(), actions_, cfg);
}

void TestGameScreenApp::setupInput()
{
    using namespace std::placeholders;

    const AppConfig& cfg = AppConfig::getInstance();

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

