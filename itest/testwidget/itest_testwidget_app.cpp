#include <iostream>
#include <botlib_app_config.h>
#include <botlib_graphics.h>
#include <botlib_button.h>
#include <botlib_label.h>
#include <itest_testwidget_app.h>

using namespace mcdane::commonlib;
using namespace mcdane::botlib;

namespace mcdane {
namespace itest {

TestWidgetApp::TestWidgetApp(const std::string& configFile,
                           const std::string& appDir)
{
    AppConfig::initInstance(configFile, appDir);

    setupWindow(1000, 800, "test widgets");

    const AppConfig& cfg = AppConfig::getInstance();
    Graphics::initInstance(cfg.simpleVertexShaderFile(),
                           cfg.simpleFragShaderFile(),
                           cfg.fontDir());

    Button::initConfig(cfg.buttonConfigFile(),
                       cfg.picDir());

    Label::initConfig(cfg.labelConfigFile());
    MessageBox::initConfig(cfg.messageBoxConfigFile());

    setupOpenGL();
    setupWidgets();
    setupInput();
}

void TestWidgetApp::preProcess()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void TestWidgetApp::process()
{
    InputManager::getInstance().processInput(inputProcessor_);

    widgets_.present();
    if (msgBox_.visible())
    {
        msgBox_.present();
    }

    glFlush();
}

void TestWidgetApp::postProcess()
{
    App::postProcess();
}

bool TestWidgetApp::processInput(const commonlib::InputEvent& e)
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
    else if (isEscPressed(e))
    {
        std::cerr << "Esc pressed" << std::endl;
        msgBox_.setVisible(true);
    }
    else
    {
        widgets_.process(e);
    }

    return true;
}

void TestWidgetApp::setupOpenGL()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Point2 viewportOrigin{viewportWidth() / 2.0f, viewportHeight() / 2.0f};
    SimpleShaderProgram& shader = Graphics::getInstance().simpleShader();

    shader.use();
    shader.setViewportSize(viewportSize());
    shader.setViewportOrigin(viewportOrigin);
}

void TestWidgetApp::setupWidgets()
{
    constexpr unsigned int BUTTON_COUNT = 3;
    float buttonWidth = 200.0f, buttonHeight = 50.0f;
    float buttonX = viewportWidth() / 2.0f;
    float buttonY = 100.0f;
    float buttonZ = 0.5f;
    float incrY = 200.0f;
    std::string buttonTexts[] = {
        "Start Game",
        "Setting",
        "Exit"
    };

    widgets_.init(BUTTON_COUNT+3);
    for (unsigned int i = 0; i < BUTTON_COUNT; ++i)
    {
        Button* button = new Button(buttonX, buttonY, buttonZ,
                                    buttonWidth, buttonHeight, buttonTexts[i]);

        button->setActionFunc(
            [=]()
            {
                std::cerr << buttonTexts[i] << " Clicked " << std::endl;
            }
        );

        widgets_.setWidget(i, button);
        buttonY += incrY;
    }

    Label* label = new Label(150.0f, 200.0f, 0.5f, 200.0f, 70.0f, "Label One");
    widgets_.setWidget(BUTTON_COUNT, label);
    label = new Label(150.0f, 400.0f, 0.5f, 200.0f, 70.0f, "Label Two",
                      TextSize::SMALL, HAlign::MIDDLE, VAlign::MIDDLE);
    widgets_.setWidget(BUTTON_COUNT+1, label);
    label = new Label(150.0f, 600.0f, 0.5f, 200.0f, 70.0f, "Label Three",
                      TextSize::SMALL, HAlign::RIGHT, VAlign::BOTTOM);
    widgets_.setWidget(BUTTON_COUNT+2, label);

    msgBox_.init(500.0f, 400.0f, 0.0f, 300.0f, 150.0f, "Test MessageBox.",
                 MessageBox::BUTTON_OK | MessageBox::BUTTON_CANCEL);
}

void TestWidgetApp::setupInput()
{
    using namespace std::placeholders;

    const AppConfig& cfg = AppConfig::getInstance();
    InputManager::initInstance(window(), viewportHeight(),
                               cfg.inputQueueCapacity());

    inputProcessor_ = std::bind(&TestWidgetApp::processInput, this, _1);

    InputManager::getInstance().enable();
}

bool TestWidgetApp::isEscPressed(const commonlib::InputEvent& e)
{
    if (e.type() != EventType::KEY)
    {
        return false;
    }

    const KeyEvent& k = e.keyEvent();
    return k.action_ == GLFW_RELEASE && k.key_ == GLFW_KEY_ESCAPE;
}

} // end of namespace itest
} // end of namespace mcdane

