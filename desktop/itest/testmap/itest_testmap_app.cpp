#include <iostream>
#include <commonlib_log.h>
#include <commonlib_file_utils.h>
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

    init(1000, 800, "test game map");

    const AppConfig& cfg = AppConfig::instance();

    Context::init(cfg);
//    setupOpenGL();
    factory_.init(1000);
    setupMap(constructPath({cfg.mapDir(), mapFile}));
}

void TestMapApp::process()
{
    glClear(GL_COLOR_BUFFER_BIT);
    map_.present();
    glFlush();
}

/*void TestMapApp::setupOpenGL()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}*/

void TestMapApp::setupMap(const std::string& mapFile)
{
    GameMapLoader loader(viewportWidth(), viewportHeight(), factory_);
    loader.load(map_, mapFile);
}

} // end of namespace itest
} // end of namespace mcdane

