#include <iostream>
#include <botlib_app_config.h>
#include <botlib_graphics.h>
#include <botlib_game_lib.h>
#include <itest_testmap_app.h>

using namespace mcdane::commonlib;
using namespace mcdane::botlib;

namespace mcdane {
namespace itest {

TestMapApp::TestMapApp(const std::string& configFile,
                       const std::string& appDir)
{
    AppConfig::initInstance(configFile, appDir);

    setupWindow(1000, 800, "test game map");

    const AppConfig& cfg = AppConfig::getInstance();

    Graphics::initInstance(cfg.simpleVertexShaderFile(),
                           cfg.simpleFragShaderFile(),
                           cfg.fontDir());

    GameLib::initInstance(cfg.textureLibFile(),
                          cfg.rectLibFile(),
                          cfg.tileTemplateLibFile(),
                          cfg.picDir());

    setupOpenGL();
    setupMap();
}

void TestMapApp::preProcess()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void TestMapApp::process()
{
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

/*    Point2 viewportOrigin{viewportWidth() / 2.0f, viewportHeight() / 2.0f};
    SimpleShaderProgram& shader = Graphics::getInstance().simpleShader();

    shader.use();
    shader.setViewportSize(viewportSize());
    shader.setViewportOrigin(viewportOrigin);*/
}

void TestMapApp::setupMap()
{
}

} // end of namespace itest
} // end of namespace mcdane

