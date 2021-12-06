#include <botlib_app_config.h>
#include <botlib_game_lib.h>
#include <botlib_graphics.h>
#include <itest_testgame_app.h>

using namespace mcdane::commonlib;
using namespace mcdane::botlib;

namespace mcdane {
namespace itest {

TestGameApp::TestGameApp(const std::string& configFile,
                         const std::string& appDir)
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
                          cfg.aiRobotTemplateLibFile());

    setupOpenGL();
    setupDeltaSmoother();
    setupMap();
    setupObjects();
}

void TestGameApp::preProcess()
{
    glClear(GL_COLOR_BUFFER_BIT);
    deltaSmoother_.updateTimeDelta();
}

void TestGameApp::process()
{
    float delta = deltaSmoother_.curTimeDelta();

    robot_->update(map_, delta);

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

void TestGameApp::setupMap()
{
    const AppConfig& cfg = AppConfig::getInstance();
    const GameLib& lib = GameLib::getInstance();
    unsigned int rows = 40, cols = 40;
    unsigned int poolSize =
            static_cast<unsigned int>(rows * cols * cfg.mapPoolSizeFactor());

    map_.init(poolSize, rows, cols, viewportWidth(), viewportHeight(),
              lib.maxObjSpan());
}

void TestGameApp::setupObjects()
{
    const GameLib& lib = GameLib::getInstance();

    const AIRobotTemplate* t = lib.findAIRobotTemplate("red_robot");
    robot_ = new AIRobot();
    robot_->init(t, 200.0f, 200.0f, -1.0f, 0.0f);
    robot_->setMovingEnabled(true);

    map_.addObj(robot_);
}

} // end of namespace itest
} // end of namespace mcdane

