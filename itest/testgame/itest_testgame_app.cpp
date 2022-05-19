#include <botlib_app_config.h>
#include <botlib_context.h>
#include <botlib_game_map_loader.h>
#include <botlib_hp_indicator.h>
#include <botlib_game_object_updater.h>
#include <botlib_game_object_flag_resetter.h>
#include <itest_testgame_app.h>

using namespace mcdane::commonlib;
using namespace mcdane::botlib;

namespace mcdane {
namespace itest {

TestGameApp::TestGameApp(const std::string& configFile,
                         const std::string& appDir,
                         const std::string& mapFile)
{
    AppConfig::init(configFile, appDir);

    setupWindow(1000, 1000, "test game mechanics");

    const AppConfig& cfg = AppConfig::instance();

    Context::init(cfg);
    setupOpenGL();
    setupDeltaSmoother();
    setupObjDumper();
    setupMap(mapFile);
}

void TestGameApp::process()
{
    deltaSmoother_.update();

    update();

    glClear(GL_COLOR_BUFFER_BIT);
    map_.present();
    glFlush();

    postProcess();
}

void TestGameApp::setupOpenGL()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_PROGRAM_POINT_SIZE);
}

void TestGameApp::setupDeltaSmoother()
{
    const AppConfig& cfg = AppConfig::instance();

    deltaSmoother_.init(cfg.timeDeltaHistoryLen());
    deltaSmoother_.start();
}

void TestGameApp::setupMap(const std::string& mapFile)
{
    GameMapLoader mapLoader(viewportWidth(), viewportHeight());
    mapLoader.load(map_, mapFile);
}

void TestGameApp::setupObjDumper()
{
    const GameScreenConfig& cfg = Context::gameScreenConfig();
    objDumper_.init(cfg.dumperPoolSize());
}

void TestGameApp::update()
{
    clearObjUpdated();
    updateObjs();

    if (!objDumper_.empty())
    {
        objDumper_.clear(map_);
    }
}

void TestGameApp::clearObjUpdated()
{
    GameObjectFlagResetter flagResetter(GameObject::FLAG_UPDATED, false);
    map_.accessRegion(map_.presentArea(), flagResetter);
}

void TestGameApp::updateObjs()
{
    GameObjectUpdater updater(map_, objDumper_, deltaSmoother_.curTimeDelta());
    map_.accessRegion(map_.presentArea(), updater);
}

} // end of namespace itest
} // end of namespace mcdane

