#include <commonlib_log.h>
#include <commonlib_input_manager.h>
#include <botlib_app_config.h>
#include <botlib_context.h>
#include <botlib_test_direction_pie_app.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

#ifdef DESKTOP_APP
void TestDirectionPieApp::init(const std::string &configFile,
          const std::string &appDir)
{
    AppConfig::init(configFile, appDir);

    const AppConfig& cfg = AppConfig::instance();
    App::init(cfg.width(), cfg.height(), "Test DirectionPie");

    setup();
}

bool TestDirectionPieApp::operator()(const InputEvent &e)
{
    if (e.type() == EventType::MOUSE_BUTTON)
    {
        const MouseButtonEvent &evt = e.mouseButtonEvent();
        if (evt.button_ == GLFW_MOUSE_BUTTON_LEFT && evt.action_ == GLFW_PRESS)
        {
            onPointerDown(evt.x_, evt.y_);
        }
    }
    else if (e.type() == EventType::MOUSE_MOVE)
    {
        const MouseMoveEvent &evt = e.mouseMoveEvent();
        onPointerOver(evt.x_, evt.y_);
    }

    return true;
}

void TestDirectionPieApp::setupInput()
{
    const AppConfig &cfg = AppConfig::instance();
    InputManager::initInstance(window(), viewportSize(),
                               cfg.inputQueueCapacity());
    InputManager::instance().enable();
}

#elif __ANDROID__
void TestDirectionPieApp::init(android_app *app,
          const std::string &configFile)
{
    AppConfig::init(configFile);

    App::init(app);

    setup();
}

bool TestDirectionPieApp::operator()(const InputEvent &e)
{
    if (e.type_ == InputEvent::POINTER_DOWN)
    {
        onPointerDown(e.x_, e.y_);
    }
    else if (e.type_ == InputEvent::POINTER_MOVE)
    {
        onPointerOver(e.x_, e.y_);
    }

    return true;
}

void TestDirectionPieApp::setupInput()
{
    InputManager::initInstance(app_, viewportSize());
}
#endif

void TestDirectionPieApp::process()
{
    App::process();
    InputManager::instance().processInput(*this);
    present();
    postProcess();
}

void TestDirectionPieApp::setup()
{
    Context::init(AppConfig::instance());
    setupShader();
    setupDirectionPie();
    setupInput();
}

void TestDirectionPieApp::present()
{
    glClear(GL_COLOR_BUFFER_BIT);
    pie_.present();
    glFlush();
}

void TestDirectionPieApp::setupShader()
{
    Point2 viewportOrigin{viewportWidth() / 2.0f, viewportHeight() / 2.0f};
    SimpleShaderProgram &shader = Context::graphics().simpleShader();

    shader.use();
    shader.setViewportSize(viewportSize());
    shader.setViewportOrigin(viewportOrigin);
}

void TestDirectionPieApp::setupDirectionPie()
{
    pie_.init(500.0f, 500.0f, {1.0f, 0.0f}, true);
}

void TestDirectionPieApp::onViewportChange(float width, float height)
{
    App::onViewportChange(width, height);
    InputManager::instance().setViewportSize(viewportSize());
    setupShader();
}

void TestDirectionPieApp::onPointerDown(float x, float y)
{
    if (pie_.containPos(x, y))
    {
        pie_.onPointerDown(x, y);
    }
}

void TestDirectionPieApp::onPointerOver(float x, float y)
{
    if (pie_.containPos(x, y))
    {
        pie_.onPointerOver(x, y);
    }
}

} // end of namespace botlib
} // end of namespace mcdane
