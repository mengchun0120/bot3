#include <iostream>
#include <botlib_app_config.h>
#include <botlib_graphics.h>
#include <botlib_game_lib.h>
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
    AppConfig::initInstance(configFile, appDir);

    setupWindow(1000, 800, "test game map");

    const AppConfig& cfg = AppConfig::getInstance();

    Graphics::initInstance(cfg.simpleVertexShaderFiles(),
                           cfg.simpleFragShaderFiles(),
                           cfg.particleVertexShaderFiles(),
                           cfg.particleFragShaderFiles(),
                           cfg.fontDir());

    GameLib::initInstance(cfg.picDir(),
                          cfg.libDir(),
                          cfg.textureLibFile(),
                          cfg.rectLibFile(),
                          cfg.componentTemplateLibFile(),
                          cfg.tileTemplateLibFile(),
                          cfg.missileTemplateLibFile(),
                          cfg.aiRobotTemplateLibFile(),
                          cfg.particleEffectTemplateLibFile());

    HPIndicator::initConfig(cfg.hpIndicatorConfigFile());

    setupOpenGL();
    setupMap(mapFile);
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

    SimpleShaderProgram& shader = Graphics::simpleShader();
    shader.use();
    shader.setViewportSize(viewportSize());
}

void TestMapApp::setupMap(const std::string& mapFile)
{
    const AppConfig& cfg = AppConfig::getInstance();

    GameMapLoader loader(cfg.mapPoolSizeFactor(), viewportWidth(), viewportHeight());
    loader.load(map_, mapFile);
}

} // end of namespace itest
} // end of namespace mcdane

