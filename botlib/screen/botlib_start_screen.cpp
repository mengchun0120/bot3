#include <functional>
#include <commonlib_log.h>
#include <commonlib_string_utils.h>
#include <botlib_button.h>
#include <botlib_context.h>
#include <botlib_start_screen_config.h>
#include <botlib_start_screen.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

StartScreen::StartScreen(const commonlib::Vector2 &viewportSize,
                         const AppActions &actions)
    : Screen(actions)
{
    if (viewportSize[0] <= 0.0f || viewportSize[1] <= 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid viewportSize " + stringVal(viewportSize));
    }

    initWidgets(viewportSize);
    prepareShader(viewportSize);
}

StartScreen::~StartScreen()
{
}

void StartScreen::update(float delta)
{
}

void StartScreen::present()
{
    glClear(GL_COLOR_BUFFER_BIT);
    widgets_.present();
    glFlush();
}

#ifdef DESKTOP_APP
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
#endif

void StartScreen::initWidgets(const commonlib::Vector2 &viewportSize)
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
    const StartScreenConfig &cfg = Context::startScreenConfig();
    float totalHeight = numButtons * cfg.buttonHeight() +
                        (numButtons - 1.0f) * cfg.buttonSpacing();
    float x = viewportSize[0] / 2.0f;
    float y = (viewportSize[1] + totalHeight - cfg.buttonHeight()) / 2.0f;
    float deltaY = cfg.buttonHeight() + cfg.buttonSpacing();

    widgets_.init(numButtons);
    for (unsigned int i = 0; i < numButtons; ++i)
    {
        Button *button = new Button(x,
                                    y,
                                    cfg.buttonWidth(),
                                    cfg.buttonHeight(),
                                    buttonTexts[i]);
        button->setActionFunc(actions[i]);
        widgets_.setWidget(i, button);

        y -= deltaY;
    }
}

void StartScreen::prepareShader(const commonlib::Vector2 &viewportSize)
{
    SimpleShaderProgram &shader = Context::graphics().simpleShader();

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
}

void StartScreen::exitGame()
{
    actions_.exitAction_();
}

#ifdef DESKTOP_APP
bool StartScreen::processMouseButtonEvent(const MouseButtonEvent &e)
{
    return true;
}

bool StartScreen::processMouseMoveEvent(const MouseMoveEvent &e)
{
    return true;
}

bool StartScreen::processKeyEvent(const KeyEvent &e)
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