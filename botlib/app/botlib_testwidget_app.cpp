#include <iostream>
#include <botlib_app_config.h>
#include <botlib_context.h>
#include <botlib_button.h>
#include <botlib_label.h>
#include <botlib_testwidget_app.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

TestWidgetApp::TestWidgetApp()
    : App()
{
}

#ifdef DESKTOP_APP
void TestWidgetApp::init(const std::string& configFile,
                         const std::string& appDir)
{
    App::init(1000, 800, "test widgets");
    AppConfig::init(configFile, appDir);
    Context::init(AppConfig::instance());
    setupShader();
    setupWidgets();
    setupInput();
}

bool TestWidgetApp::operator()(const commonlib::InputEvent& e)
{
    if (msgBox_.visible())
    {
        msgBox_.process(e);
        if (msgBox_.buttonClicked() == MessageBox::BUTTON_OK)
        {
            std::cerr << "OK clicked" << std::endl;
        }
        else if(msgBox_.buttonClicked() == MessageBox::BUTTON_CANCEL)
        {
            std::cerr << "Cancel clicked" << std::endl;
        }
    }
    else
    {
        widgets_.process(e);
    }

    return true;
}

#elif __ANDROID__

void TestWidgetApp::init(android_app *app)
{
    App::init(app);
    AppConfig::init("config/bot_config_android.json");
    Context::init(AppConfig::instance());
    setupShader();
    setupWidgets();
    setupInput(app);
}

bool TestWidgetApp::operator()(const commonlib::InputEvent& e)
{
    LOG_INFO << e << LOG_END;
    return true;
}

#endif

void TestWidgetApp::process()
{
    InputManager &inputMgr = InputManager::instance();

#ifdef __ANDROID__
    if (updateViewport())
    {
        inputMgr.resetViewport(width_, height_, viewportSize_);
    }
#endif

    inputMgr.processInput(*this);

    glClear(GL_COLOR_BUFFER_BIT);

    widgets_.present();
    if (msgBox_.visible())
    {
        msgBox_.present();
    }

    glFlush();

    postProcess();
}

void TestWidgetApp::setupShader()
{
    Point2 viewportOrigin{viewportWidth() / 2.0f, viewportHeight() / 2.0f};
    SimpleShaderProgram& shader = Context::graphics().simpleShader();

    shader.use();
    shader.setViewportSize(viewportSize());
    shader.setViewportOrigin(viewportOrigin);

    fillColor_.init({255, 125, 0, 255});
}

void TestWidgetApp::setupWidgets()
{
    constexpr unsigned int BUTTON_COUNT = 3;
    float buttonWidth = 200.0f, buttonHeight = 50.0f;
    float buttonX = viewportWidth() / 2.0f;
    float buttonY = 100.0f;
    float incrY = 200.0f;
    std::string buttonTexts[] = {
        "Start Game",
        "Setting",
        "Exit"
    };
    Button::ActionFunc actions[] = {
        std::bind(&TestWidgetApp::onStartGameClicked, this),
        std::bind(&TestWidgetApp::onSettingClicked, this),
        std::bind(&TestWidgetApp::onExitClicked, this)
    };


    widgets_.init(BUTTON_COUNT+3);
    for (unsigned int i = 0; i < BUTTON_COUNT; ++i)
    {
        Button* button = new Button(buttonX, buttonY,
                                    buttonWidth, buttonHeight, buttonTexts[i]);
        button->setActionFunc(actions[i]);
        widgets_.setWidget(i, button);
        buttonY += incrY;
    }

    Label* label = new Label(150.0f, 200.0f, 200.0f, 70.0f, "Label One");
    widgets_.setWidget(BUTTON_COUNT, label);
    label = new Label(150.0f, 400.0f, 200.0f, 70.0f, "Label Two",
                      TextSize::SMALL, HAlign::MIDDLE, VAlign::MIDDLE);
    widgets_.setWidget(BUTTON_COUNT+1, label);
    label = new Label(150.0f, 600.0f, 200.0f, 70.0f, "Label Three",
                      TextSize::SMALL, HAlign::RIGHT, VAlign::BOTTOM);
    widgets_.setWidget(BUTTON_COUNT+2, label);

    msgBox_.init(500.0f, 400.0f, 300.0f, 150.0f, "", MessageBox::BUTTON_NONE);
}

#ifdef DESKTOP_APP

void TestWidgetApp::setupInput()
{
    const AppConfig& cfg = AppConfig::instance();
    InputManager::initInstance(window(), viewportHeight(),
                               cfg.inputQueueCapacity());
}

#elif __ANDROID__

void TestWidgetApp::setupInput(android_app *app)
{
    InputManager::initInstance(app, width_, height_, viewportSize_);
}

#endif


void TestWidgetApp::onStartGameClicked()
{
    msgBox_.setText("You clicked start game");
    msgBox_.setButtons(MessageBox::BUTTON_OK | MessageBox::BUTTON_CANCEL);
    msgBox_.setVisible(true);
}

void TestWidgetApp::onSettingClicked()
{
    msgBox_.setText("You clicked Setting");
    msgBox_.setButtons(MessageBox::BUTTON_OK);
    msgBox_.setVisible(true);
}

void TestWidgetApp::onExitClicked()
{
    msgBox_.setText("You clicked Exit");
    msgBox_.setButtons(MessageBox::BUTTON_CANCEL);
    msgBox_.setVisible(true);
}

} // end of namespace botlib
} // end of namespace mcdane

