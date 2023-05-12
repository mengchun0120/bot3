#include <iostream>
#include <commonlib_input_manager.h>
#include <botlib_app_config.h>
#include <botlib_context.h>
#include <botlib_button.h>
#include <botlib_label.h>
#include <botlib_text_box.h>
#include <botlib_test_widget_app.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

TestWidgetApp::TestWidgetApp()
    : App("testwidget")
{
}

#ifdef DESKTOP_APP
void TestWidgetApp::init(const std::string &configFile,
                         const std::string &appDir)
{
    App::init(1000, 800, "test widgets");
    AppConfig::init(configFile, appDir);
    Context::init(AppConfig::instance());
    setupShader();
    setupWidgets();
    setupInput();
    setupDeltaSmoother();
}
#elif __ANDROID__
void TestWidgetApp::init(android_app *app,
                         const std::string &configFile)
{
    App::init(app);
    AppConfig::init(configFile);
    Context::init(AppConfig::instance());
    setupShader();
    setupWidgets();
    setupInput();
    setupDeltaSmoother();
}
#endif

void TestWidgetApp::process()
{
    App::process();
    InputManager::instance().processInput(*this);
    update();
    present();
    postProcess();
}

bool TestWidgetApp::operator()(const commonlib::InputEvent &e)
{
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
    SimpleShaderProgram &shader = Context::graphics().simpleShader();

    shader.use();
    shader.setViewportSize(viewportSize());
    shader.setViewportOrigin(viewportOrigin);
}

void TestWidgetApp::setupWidgets()
{
    widgets_.init(k_buttonCount + 4);
    setupButtons();
    setupLabels();
    setupTextBox();
    setupMessageBox();
}

void TestWidgetApp::setupButtons()
{
    float buttonWidth = 300.0f, buttonHeight = 100.0f;
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

    for (unsigned int i = 0; i < k_buttonCount; ++i)
    {
        Button *button = new Button(buttonX, buttonY,
                                    buttonWidth, buttonHeight, buttonTexts[i]);
        button->setActionFunc(actions[i]);
        widgets_.setWidget(i, button);
        buttonY += incrY;
    }
}

void TestWidgetApp::setupLabels()
{
    Label *label = new Label(150.0f, 200.0f, 200.0f, 70.0f, "Label One");
    widgets_.setWidget(k_buttonCount, label);

    label = new Label(150.0f, 400.0f, 200.0f, 70.0f, "Label Two",
                      TextSize::SMALL, HAlign::MIDDLE, VAlign::MIDDLE);
    widgets_.setWidget(k_buttonCount + 1, label);

    label = new Label(150.0f, 600.0f, 200.0f, 70.0f, "Label Three",
                      TextSize::SMALL, HAlign::RIGHT, VAlign::BOTTOM);
    widgets_.setWidget(k_buttonCount + 2, label);
}

void TestWidgetApp::setupTextBox()
{
    TextBox *textBox = new TextBox();
    textBox->init(400.0f, 600.0f, 300.0f, 40.0f);
    widgets_.setWidget(k_buttonCount + 3, textBox);
}

void TestWidgetApp::setupMessageBox()
{
    msgBox_.init(500.0f, 400.0f, 300.0f, 150.0f, "", MessageBox::BUTTON_NONE);
}

#ifdef DESKTOP_APP
void TestWidgetApp::setupInput()
{
    const AppConfig &cfg = AppConfig::instance();
    InputManager::initInstance(window(), viewportSize(),
                               cfg.inputQueueCapacity());
    InputManager::instance().enable();
}
#elif __ANDROID__
void TestWidgetApp::setupInput()
{
    InputManager::initInstance(app_, viewportSize());
}
#endif

void TestWidgetApp::setupDeltaSmoother()
{
    const AppConfig& cfg = AppConfig::instance();

    deltaSmoother_.init(cfg.timeDeltaHistoryLen());
    deltaSmoother_.start();
}

void TestWidgetApp::update()
{
    deltaSmoother_.update();
    widgets_.update(deltaSmoother_.curTimeDelta());
}

void TestWidgetApp::present()
{
    glClear(GL_COLOR_BUFFER_BIT);

    widgets_.present();
    if (msgBox_.visible())
    {
        msgBox_.present();
    }

    glFlush();
}

void TestWidgetApp::onViewportChange(float width, float height)
{
    App::onViewportChange(width, height);
    InputManager::instance().setViewportSize(viewportSize());
    setupShader();
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

