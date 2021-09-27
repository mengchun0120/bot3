#include <iostream>
#include <functional>
#include <commonlib_log.h>
#include <commonlib_json_param.h>
#include <botlib_button.h>
#include <botlib_graphics.h>
#include <botlib_start_screen.h>
#include <botlib_screen_manager.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

float StartScreen::k_buttonWidth;
float StartScreen::k_buttonHeight;
float StartScreen::k_buttonSpacing;

void StartScreen::initConfig(const rapidjson::Value& cfg)
{
    if (!cfg.IsObject())
    {
        THROW_EXCEPT(InvalidArgumentException, "cfg must be an object");
    }

    std::vector<JsonParamPtr> params{
        jsonParam(k_buttonWidth, {"buttonWidth"}, true,
                  gt(k_buttonWidth, 0.0f)),
        jsonParam(k_buttonHeight, {"buttonHeight"}, true,
                  gt(k_buttonHeight, 0.0f)),
        jsonParam(k_buttonSpacing, {"buttonSpacing"}, true,
                  gt(k_buttonSpacing, 0.0f))
    };

    parse(params, cfg);
}

StartScreen::StartScreen(const commonlib::Vector2& viewportSize,
                         const AppActions& actions)
    : Screen(actions)
{
    if (viewportSize[0] <= 0.0f || viewportSize[1] <= 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid viewportSize " + toString(viewportSize));
    }

    initWidgets(viewportSize);
    prepareShader(viewportSize);
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
    if (e.type() == EventType::KEY)
    {
        if (!processKeyEvent(e.keyEvent()))
        {
            return false;
        }
    }

    widgets_.process(e);
    return true;
}

void StartScreen::initWidgets(const commonlib::Vector2& viewportSize)
{
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
    float x = viewportSize[0] / 2.0f;
    float y = (viewportSize[1] + totalHeight - k_buttonHeight) / 2.0f;
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

void StartScreen::prepareShader(const commonlib::Vector2& viewportSize)
{
    SimpleShaderProgram& shader = Graphics::getInstance().simpleShader();

    shader.use();
    shader.setViewportOrigin(viewportSize / 2.0f);
    shader.setViewportSize(viewportSize);
}

void StartScreen::startGame()
{
    actions_.switchAction_(ScreenType::GAME);
}

void StartScreen::showSettings()
{
    std::cerr << "Show Settings" << std::endl;
}

void StartScreen::exitGame()
{
    actions_.exitAction_();
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
    if (GLFW_KEY_ESCAPE == e.key_)
    {
        actions_.exitAction_();
        return false;
    }
    return true;
}
#endif

} // end of namespace botlib
} // end of namespace mcdane

