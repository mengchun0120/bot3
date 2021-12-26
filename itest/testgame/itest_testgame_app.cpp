#include <botlib_app_config.h>
#include <botlib_game_lib.h>
#include <botlib_graphics.h>
#include <botlib_game_map_loader.h>
#include <botlib_hp_indicator.h>
#include <itest_testgame_app.h>

using namespace mcdane::commonlib;
using namespace mcdane::botlib;

namespace mcdane {
namespace itest {

TestGameApp::TestGameApp(const std::string& configFile,
                         const std::string& appDir,
                         const std::string& mapFile)
{
    AppConfig::initInstance(configFile, appDir);

    setupWindow(1000, 1000, "test game mechanics");

    const AppConfig& cfg = AppConfig::getInstance();

    Graphics::initInstance(cfg.simpleVertexShaderFiles(),
                           cfg.simpleFragShaderFiles(),
                           cfg.fontDir());

    GameLib::initInstance(cfg.picDir(),
                          cfg.textureLibFile(),
                          cfg.rectLibFile(),
                          cfg.componentTemplateLibFile(),
                          cfg.tileTemplateLibFile(),
                          cfg.missileTemplateLibFile(),
                          cfg.aiRobotTemplateLibFile());

    HPIndicator::initConfig(cfg.hpIndicatorConfigFile());

    setupOpenGL();
    setupDeltaSmoother();
    setupMap(mapFile);
    setupGameObjUpdater();
    setupFlagAccessor();
}

void TestGameApp::preProcess()
{
    glClear(GL_COLOR_BUFFER_BIT);
    deltaSmoother_.updateTimeDelta();
}

void TestGameApp::process()
{
    update();
    map_.present();
    glFlush();
}

void TestGameApp::postProcess()
{
    App::postProcess();
}

void TestGameApp::setupOpenGL()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    SimpleShaderProgram& shader = Graphics::simpleShader();
    shader.use();
    shader.setViewportSize(viewportSize());
}

void TestGameApp::setupDeltaSmoother()
{
    const AppConfig& cfg = AppConfig::getInstance();

    deltaSmoother_.init(cfg.timeDeltaHistoryLen());
    deltaSmoother_.start();
}

void TestGameApp::setupMap(const std::string& mapFile)
{
    const AppConfig& cfg = AppConfig::getInstance();
    GameMapLoader mapLoader(cfg.mapPoolSizeFactor(), viewportWidth(),
                            viewportHeight());
    mapLoader.load(map_, mapFile);
}

void TestGameApp::setupGameObjUpdater()
{
    using namespace std::placeholders;

    gameObjUpdater_.setMap(&map_);
    updater_ = std::bind(&GameObjectUpdater::run, &gameObjUpdater_, _1);
}

void TestGameApp::setupFlagAccessor()
{
    using namespace std::placeholders;

    flagResetter_.reset(GameObject::FLAG_UPDATED, false);
    flagAccessor_ = std::bind(&GameObjectFlagResetter::run, &flagResetter_, _1);
}

void TestGameApp::update()
{
    const Region<int>& presentArea = map_.presentArea();

    map_.accessRegion(presentArea, flagAccessor_);

    gameObjUpdater_.setDelta(deltaSmoother_.curTimeDelta());
    map_.accessRegion(presentArea, updater_);
}

} // end of namespace itest
} // end of namespace mcdane

