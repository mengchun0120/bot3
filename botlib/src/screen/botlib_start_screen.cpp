#include <functional>
#include <commonlib_log.h>
#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
#include <botlib_button.h>
#include <botlib_bot_app.h>
#include <botlib_graphics.h>
#include <botlib_start_screen.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

float StartScreen::k_buttonWidth;
float StartScreen::k_buttonHeight;
float StartScreen::k_buttonSpacing;

void StartScreen::initConfig(const std::string& configFile)
{
    rapidjson::Document doc;
    readJson(doc, configFile);

    std::vector<JsonParamPtr> params{
        jsonParam(k_buttonWidth, {"buttonWidth"}, true,
                  gt(k_buttonWidth, 0.0f)),
        jsonParam(k_buttonHeight, {"buttonHeight"}, true,
                  gt(k_buttonHeight, 0.0f)),
        jsonParam(k_buttonSpacing, {"buttonSpacing"}, true,
                  gt(k_buttonSpacing, 0.0f))
    };

    parse(params, doc);
}

StartScreen::StartScreen()
{
    initWidgets();
    prepareShader();
}

StartScreen::~StartScreen()
{
}

void StartScreen::update()
{
}

void StartScreen::present()
{
    widgets_.present();
    glFlush();
}

bool StartScreen::processInput(const InputEvent &e)
{
    widgets_.process(e);
    return true;
}

void StartScreen::initWidgets()
{
    const BotApp& app = BotApp::getInstance();
    std::vector<std::string> buttonTexts{
        "Start Game",
        "Settings",
        "Exit"
    };
    std::vector<Button::ActionFunc> actions{
        std::bind(&StartScreen::startGame, this),
        std::bind(&StartScreen::showSettings, this),
        std::bind(&StartScreen::exitGame, this)
    };
    unsigned int numButtons = buttonTexts.size();
    float totalHeight = numButtons * k_buttonHeight +
                        (numButtons - 1.0f) * k_buttonSpacing;
    float y = (app.viewportHeight() + totalHeight - k_buttonHeight) / 2.0f;
    float x = app.viewportWidth() / 2.0f;
    float z = 0.0f;
    float deltaY = k_buttonHeight + k_buttonSpacing;

    widgets_.init(numButtons);
    for (unsigned int i = 0; i < numButtons; ++i)
    {
        Button* button = new Button(x, y, z, k_buttonWidth, k_buttonHeight,
                                    buttonTexts[i]);
        button->setActionFunc(actions[i]);
        widgets_.setWidget(i, button);

        y -= deltaY;
    }
}

void StartScreen::prepareShader()
{
    const BotApp& app = BotApp::getInstance();
    SimpleShaderProgram& shader = Graphics::getInstance().simpleShader();

    shader.setViewportOrigin(app.viewportSize() / 2.0f);
    shader.setViewportSize(app.viewportSize());
    shader.use();
}

void StartScreen::startGame()
{
}

void StartScreen::showSettings()
{
}

void StartScreen::exitGame()
{
}

#ifdef DESKTOP_APP
bool StartScreen::processMouseButtonEvent(const MouseButtonEvent& e)
{
    return true;
}

bool StartScreen::processMouseMoveEvent(const MouseMoveEvent& e)
{
    return true;
}

bool StartScreen::processKeyEvent(const KeyEvent& e)
{
    BotApp& app = BotApp::getInstance();

    if (GLFW_KEY_ESCAPE == e.key_)
    {
        app.setRunning(false);
        return false;
    }
    return true;
}
#endif

} // end of namespace botlib
} // end of namespace mcdane

