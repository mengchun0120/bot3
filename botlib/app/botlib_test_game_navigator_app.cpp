#include <iostream>
#include <commonlib_log.h>
#include <commonlib_input_manager.h>
#include <botlib_app_config.h>
#include <botlib_context.h>
#include <botlib_test_game_navigator_app.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

#ifdef DESKTOP_APP
void TestGameNavigatorApp::init(const std::string &configFile,
                                const std::string &appDir)
{
    AppConfig::init(configFile, appDir);

    const AppConfig& cfg = AppConfig::instance();

    App::init(cfg.width(), cfg.height(), "Test Game Navigator");
    Context::init(cfg);
    setupShader();
    setupWidgets();
    setupInput();
}
#elif __ANDROID__
void TestGameNavigatorApp::init(android_app *app,
                                const std::string &configFile)
{
    AppConfig::init(configFile);

    const AppConfig& cfg = AppConfig::instance();

    App::init(app);
    Context::init(cfg);
    setupShader();
    setupWidgets();
    setupInput();
}
#endif

void TestGameNavigatorApp::process()
{
    App::process();

    InputManager::instance().processInput(*this);

    glClear(GL_COLOR_BUFFER_BIT);
    navigator_.present();
    glFlush();

    postProcess();
}

#ifdef DESKTOP_APP
bool TestGameNavigatorApp::operator()(const InputEvent &e)
{
    if (e.type() != EventType::MOUSE_BUTTON)
    {
        return true;
    }

    const MouseButtonEvent &evt = e.mouseButtonEvent();
    if (evt.button_ == GLFW_MOUSE_BUTTON_LEFT && evt.action_ == GLFW_PRESS)
    {
        onPointer(evt.x_, evt.y_);
    }

    return true;
}
#elif __ANDROID__
bool TestGameNavigatorApp::operator()(const InputEvent &e)
{
    if (e.type_ == InputEvent::POINTER_DOWN)
    {
        onPointer(e.x_, e.y_);
    }

    return true;
}
#endif

void TestGameNavigatorApp::setupShader()
{
    Point2 viewportOrigin{viewportWidth() / 2.0f, viewportHeight() / 2.0f};
    SimpleShaderProgram &shader = Context::graphics().simpleShader();

    shader.use();
    shader.setViewportSize(viewportSize());
    shader.setViewportOrigin(viewportOrigin);
}

void TestGameNavigatorApp::setupWidgets()
{
    auto moveAction = [&](const Vector2 &direction)
    {
#ifdef DESKTOP_APP
        std::cout << "Move " << direction << std::endl;
#elif __ANDROID__
        LOG_INFO << "Move " << direction << LOG_END;
#endif
    };
    auto stopAction = [&]()
    {
#ifdef DESKTOP_APP
        std::cout << "Stop" << std::endl;
#elif __ANDROID__
        LOG_INFO << "Stop" << LOG_END;
#endif
    };

    navigator_.init(250.0f, 250.0f, moveAction, stopAction);
}

#ifdef DESKTOP_APP
void TestGameNavigatorApp::setupInput()
{
    const AppConfig &cfg = AppConfig::instance();
    InputManager::initInstance(window(), viewportSize(),
                               cfg.inputQueueCapacity());
    InputManager::instance().enable();
}
#elif __ANDROID__
void TestGameNavigatorApp::setupInput()
{
    InputManager::initInstance(app_, viewportSize());
}
#endif

void TestGameNavigatorApp::onViewportChange(float width, float height)
{
    App::onViewportChange(width, height);
    InputManager::instance().setViewportSize(viewportSize());
    setupShader();
}

void TestGameNavigatorApp::onPointer(float x, float y)
{
    if (navigator_.containPos(x, y))
    {
        navigator_.onPointerDown(x, y);
    }
}

} // end of namespace botlib
} // end of namespace mcdane
