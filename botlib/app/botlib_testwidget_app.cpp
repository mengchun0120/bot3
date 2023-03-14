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
#endif

void TestWidgetApp::process()
{
    App::process();

    InputManager::instance().processInput(*this);

    glClear(GL_COLOR_BUFFER_BIT);

    widgets_.present();
    if (msgBox_.visible())
    {
        msgBox_.present();
    }

    glFlush();

    postProcess();
}

bool TestWidgetApp::operator()(const commonlib::InputEvent& e)
{
    LOG_INFO << "Process " << e << LOG_END;

    if (msgBox_.visible())
    {
        msgBox_.process(e);
        if (msgBox_.buttonClicked() == MessageBox::BUTTON_OK)
        {
            LOG_INFO << "OK clicked" << LOG_END;
        }
        else if(msgBox_.buttonClicked() == MessageBox::BUTTON_CANCEL)
        {
            LOG_INFO << "Cancel clicked" << LOG_END;
        }
    }
    else
    {
        widgets_.process(e);
    }

    return true;
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
    float buttonWidth = 300.0f, buttonHeight = 100.0f;
    float buttonX = viewportWidth() / 2.0f;
    float buttonY = 0.0f;
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
    InputManager::instance().enable();
}

#elif __ANDROID__

void TestWidgetApp::setupInput(android_app *app)
{
    InputManager::initInstance(app, width_, height_, viewportSize_);
}

#endif

void TestWidgetApp::onViewportChange(float width1, float height1)
{
    App::onViewportChange(width1, heigh1);

}

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

