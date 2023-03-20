#include <commonlib_log.h>
#include <commonlib_file_utils.h>
#include <botlib_app_config.h>
#include <botlib_context.h>
#include <botlib_hp_indicator.h>
#include <botlib_game_map_loader.h>
#include <botlib_test_map_app.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

TestMapApp::TestMapApp()
    : App()
{
}

#ifdef DESKTOP_APP
void TestMapApp::init(const std::string &configFile,
                      const std::string &appDir,
                      const std::string &mapFile)
{
    AppConfig::init(configFile, appDir);
    App::init(1000, 800, "test game map");

    const AppConfig &cfg = AppConfig::instance();

    Context::init(cfg);
    factory_.init(1000);
    setupMap(constructPath({cfg.mapDir(), mapFile}));
}
#elif __ANDROID__
void TestMapApp::init(android_app *app,
                      const std::string &configFile,
                      const std::string &mapFile)
{
    AppConfig::init(configFile);
    App::init(app);

    const AppConfig &cfg = AppConfig::instance();

    Context::init(cfg);
    factory_.init(1000);
    setupMap(constructPath({cfg.mapDir(), mapFile}));
}
#endif

void TestMapApp::process()
{
    App::process();

    glClear(GL_COLOR_BUFFER_BIT);
    map_.present();
    glFlush();

    postProcess();
}

void TestMapApp::setupMap(const std::string &mapFile)
{
    GameMapLoader loader(viewportWidth(), viewportHeight(), factory_);
    loader.load(map_, mapFile);
}

void TestMapApp::onViewportChange(float width, float height)
{
    LOG_INFO << "Viewport change " << width << " " << height << LOG_END;

    App::onViewportChange(width, height);
    map_.resetViewport(width, height);
}

} // end of namespace botlib
} // end of namespace mcdane

