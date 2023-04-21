#include <commonlib_log.h>
#include <commonlib_input_manager.h>
#include <botlib_app_config.h>
#include <botlib_context.h>
#include <botlib_test_game_navigator_app.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

#ifdef DESKTOP_APP
#define LOG std::cout
#define END std::endl
#elif __ANDROID__
#define LOG LOG_INFO
#define END LOG_END
#endif

#ifdef DESKTOP_APP
void TestGameNavigatorApp::init(const std::string &configFile,
                                const std::string &appDir)
{
    AppConfig::init(configFile, appDir);

    const AppConfig& cfg = AppConfig::instance();
    App::init(cfg.width(), cfg.height(), "Test GameNavigator");

    setup();
}

bool TestGameNavigatorApp::operator()(const InputEvent &e)
{
    if (e.type() == EventType::MOUSE_BUTTON)
    {
        const MouseButtonEvent &evt = e.mouseButtonEvent();
        if (evt.button_ == GLFW_MOUSE_BUTTON_LEFT)
        {
            if (evt.action_ == GLFW_PRESS)
            {
                onPointerDown(evt.x_, evt.y_);
            }
            else
            {
                onPointerUp(evt.x_, evt.y_);
            }
        }
    }
    else if (e.type() == EventType::MOUSE_MOVE)
    {
        const MouseMoveEvent &evt = e.mouseMoveEvent();
        onPointerOver(evt.x_, evt.y_);
    }

    return true;
}

void TestGameNavigatorApp::setupInput()
{
    const AppConfig &cfg = AppConfig::instance();
    InputManager::initInstance(window(), viewportSize(),
                               cfg.inputQueueCapacity());
    InputManager::instance().enable();
}

#elif __ANDROID__
void TestGameNavigatorApp::init(android_app *app,
          const std::string &configFile)
{
    AppConfig::init(configFile);

    App::init(app);

    setup();
}

bool TestGameNavigatorApp::operator()(const InputEvent &e)
{
    if (e.type_ == InputEvent::POINTER_DOWN)
    {
        onPointerDown(e.x_, e.y_);
    }
    else if (e.type_ == InputEvent::POINTER_MOVE)
    {
        onPointerOver(e.x_, e.y_);
    }
    else if (e.type_ == InputEvent::POINTER_UP)
    {
        onPointerUp(e.x_, e.y_);
    }

    return true;
}

void TestGameNavigatorApp::setupInput()
{
    InputManager::initInstance(app_, viewportSize());
}
#endif

void TestGameNavigatorApp::process()
{
    App::process();
    InputManager::instance().processInput(*this);
    present();
    postProcess();
}

void TestGameNavigatorApp::setup()
{
    Context::init(AppConfig::instance());
    setupShader();
    setupNavigator();
    setupInput();
}

void TestGameNavigatorApp::present()
{
    glClear(GL_COLOR_BUFFER_BIT);

    navigator_.present();

    glFlush();
}

void TestGameNavigatorApp::setupShader()
{
    Point2 viewportOrigin{viewportWidth() / 2.0f, viewportHeight() / 2.0f};
    SimpleShaderProgram &shader = Context::graphics().simpleShader();

    shader.use();
    shader.setViewportSize(viewportSize());
    shader.setViewportOrigin(viewportOrigin);
}

void TestGameNavigatorApp::setupNavigator()
{
    using namespace std::placeholders;

    Vector2 p;
    GameNavigator::SteerFunc steerFunc = std::bind(&TestGameNavigatorApp::onSteer,
                                                   this, _1);

    calculateNavigatorPos(p);
    navigator_.init(p[0], p[1], steerFunc);
}

void TestGameNavigatorApp::onViewportChange(float width, float height)
{
    App::onViewportChange(width, height);
    InputManager::instance().setViewportSize(viewportSize());
    setupShader();
    resetNavigatorPos();
}

void TestGameNavigatorApp::calculateNavigatorPos(Vector2 &p)
{
    const GameScreenConfig &cfg = Context::gameScreenConfig();
    p[0] = cfg.navigatorLeftSpacing();
    p[1] = cfg.navigatorBottomSpacing();
}

void TestGameNavigatorApp::onSteer(const commonlib::Vector2 &direction)
{
    LOG << "onSteer direction=" << direction << END;
}

void TestGameNavigatorApp::resetNavigatorPos()
{
    Vector2 pos;
    calculateNavigatorPos(pos);
    navigator_.setPos(pos[0], pos[1]);
}

void TestGameNavigatorApp::onPointerDown(float x, float y)
{
    if (navigator_.containPos(x, y))
    {
        navigator_.onPointerDown(x, y);
    }
    else
    {
        navigator_.disableDirection();
    }
}

void TestGameNavigatorApp::onPointerOver(float x, float y)
{
    if (navigator_.containPos(x, y))
    {
        navigator_.onPointerOver(x, y);
    }
    else
    {
        navigator_.disableDirection();
    }
}

void TestGameNavigatorApp::onPointerUp(float x, float y)
{
    navigator_.onPointerUp(x, y);
}

} // end of namespace botlib
} // end of namespace mcdane
