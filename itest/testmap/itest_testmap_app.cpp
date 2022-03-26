#include <iostream>
#include <commonlib_log.h>
#include <botlib_app_config.h>
#include <botlib_context.h>
#include <botlib_hp_indicator.h>
#include <botlib_game_map_loader.h>
#include <itest_testmap_app.h>

using namespace mcdane::commonlib;
using namespace mcdane::botlib;

namespace mcdane {
namespace itest {

TestMapApp::TestMapApp(const std::string& configFile,
                       const std::string& appDir,
                       const std::string& mapFile)
{
    AppConfig::init(configFile, appDir);

    setupWindow(1000, 800, "test game map");

    const AppConfig& cfg = AppConfig::instance();

    Context::init(cfg);
    HPIndicator::initConfig(cfg.hpIndicatorConfigFile());

    LOG_INFO << "HPIndicator" << LOG_END;

    setupOpenGL();

    LOG_INFO << "setupOpenGL" << LOG_END;

    setupMap(mapFile);

    LOG_INFO << "setupMap" << LOG_END;
}

void TestMapApp::preProcess()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void TestMapApp::process()
{
    map_.present();
    glFlush();
}

void TestMapApp::postProcess()
{
    App::postProcess();
}

void TestMapApp::setupOpenGL()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void TestMapApp::setupMap(const std::string& mapFile)
{
    GameMapLoader loader(viewportWidth(), viewportHeight());
    loader.load(map_, mapFile);
}

} // end of namespace itest
} // end of namespace mcdane

