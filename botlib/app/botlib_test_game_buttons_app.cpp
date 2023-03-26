#include <iostream>
#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_input_manager.h>
#include <botlib_app_config.h>
#include <botlib_context.h>
#include <botlib_game_navigator.h>
#include <botlib_skill_button.h>
#include <botlib_test_game_buttons_app.h>

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
void TestGameButtonsApp::init(const std::string &configFile,
                              const std::string &appDir)
{
    AppConfig::init(configFile, appDir);

    const AppConfig& cfg = AppConfig::instance();
    App::init(cfg.width(), cfg.height(), "Test Game Buttons");

    setup();
}
#elif __ANDROID__
void TestGameButtonsApp::init(android_app *app,
                              const std::string &configFile)
{
    AppConfig::init(configFile);

    App::init(app);

    setup();
}
#endif

void TestGameButtonsApp::process()
{
    App::process();

    InputManager::instance().processInput(*this);
    deltaSmoother_.update();

    update(deltaSmoother_.curTimeDelta());
    present();

    postProcess();
}

bool TestGameButtonsApp::operator()(const InputEvent &e)
{
    widgets_.process(e);
    return true;
}

void TestGameButtonsApp::setup()
{
    Context::init(AppConfig::instance());
    setupShader();
    setupCoolDownDurations();
    setupWidgets();
    setupDeltaSmoother();
    setupInput();
}

void TestGameButtonsApp::update(float timeDelta)
{
    for (int i = 0; i < k_numSkillButtons; ++i)
    {
        SkillButton *button = widgets_.widget<SkillButton>(i+1);

        durations_[i] += timeDelta;
        button->setRatio(durations_[i] / coolDowns_[i]);

        if (durations_[i] >= coolDowns_[i])
        {
            button->setEnabled(true);
        }
    }
}

void TestGameButtonsApp::present()
{
    glClear(GL_COLOR_BUFFER_BIT);

    widgets_.present();

    glFlush();
}

void TestGameButtonsApp::setupShader()
{
    Point2 viewportOrigin{viewportWidth() / 2.0f, viewportHeight() / 2.0f};
    SimpleShaderProgram &shader = Context::graphics().simpleShader();

    shader.use();
    shader.setViewportSize(viewportSize());
    shader.setViewportOrigin(viewportOrigin);
}

void TestGameButtonsApp::setupCoolDownDurations()
{
    coolDowns_.assign({1000.0f, 5000.0f, 10000.0f});
    durations_.assign(coolDowns_.begin(), coolDowns_.end());
}

void TestGameButtonsApp::setupWidgets()
{
    widgets_.init(k_numSkillButtons + 1);
    setupGameNavigator();
    setupSkillButtons();
}

void TestGameButtonsApp::setupDeltaSmoother()
{
    const AppConfig &cfg = AppConfig::instance();
    deltaSmoother_.init(cfg.timeDeltaHistoryLen());
    deltaSmoother_.start();
}

#ifdef DESKTOP_APP
void TestGameButtonsApp::setupInput()
{
    const AppConfig &cfg = AppConfig::instance();
    InputManager::initInstance(window(), viewportSize(),
                               cfg.inputQueueCapacity());
    InputManager::instance().enable();
}
#elif __ANDROID__
void TestGameButtonsApp::setupInput()
{
    InputManager::initInstance(app_, viewportSize());
}
#endif

void TestGameButtonsApp::setupGameNavigator()
{
    const GameScreenConfig &cfg = Context::gameScreenConfig();

    auto steerFunc = [&](const Vector2 &direction)
    {
        LOG << "Steer " << direction << END;
    };
    auto toggleFunc = [&]()
    {
        LOG << "Toggle" << END;
    };

    GameNavigator *navigator = new GameNavigator();
    navigator->init(cfg.navigatorLeftSpacing(), cfg.navigatorBottomSpacing(),
                    steerFunc, toggleFunc);
    widgets_.setWidget(0, navigator);
}

void TestGameButtonsApp::setupSkillButtons()
{
    std::vector<std::string> pieTemplates{
        "shoot_missile_skill_progress_pie",
        "blast_skill_progress_pie",
        "barrage_skill_progress_pie",
    };
    std::vector<float> coolDowns{
        5000.0f, 10000.0f, 15000.0f
    };
    std::vector<std::string> actionMsgs{
        "Shoot Missile", "Blast", "Barrage"
    };

    buttonPositions_.resize(k_numSkillButtons);
    calculateButtonPositions();
    for (int i = 0; i < k_numSkillButtons; ++i)
    {
        addSkillButton(i+1, buttonPositions_[i][0], buttonPositions_[i][1],
                       pieTemplates[i], actionMsgs[i]);
    }
}

void TestGameButtonsApp::addSkillButton(
        int idx,
        float x,
        float y,
        const std::string &pieTemplate,
        const std::string &actionMsg)
{
    const GameLib &lib = Context::gameLib();
    const ProgressPieTemplate *t = lib.findProgressPieTemplate(pieTemplate);
    if (!t)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Faild to find ProgreePie " + pieTemplate);
    }

    auto action = [this, idx, actionMsg](SkillButton &button)
    {
        button.setEnabled(false);
        durations_[idx-1] = 0.0f;

        LOG << actionMsg << END;
    };

    SkillButton *button = new SkillButton();
    button->init(x, y, t, action);
    widgets_.setWidget(idx, button);
}

void TestGameButtonsApp::calculateButtonPositions()
{
    const GameScreenConfig &cfg = Context::gameScreenConfig();
    float y = cfg.skillButtonBottomSpacing();
    float x = viewportWidth() - cfg.skillButtonRightSpacing() -
              (k_numSkillButtons - 1) * cfg.skillButtonSpacing();

    for (int i = 0; i < k_numSkillButtons; ++i)
    {
        buttonPositions_[i][0] = x;
        buttonPositions_[i][1] = y;
        x += cfg.skillButtonSpacing();
    }
}

void TestGameButtonsApp::onViewportChange(float width, float height)
{
    App::onViewportChange(width, height);
    InputManager::instance().setViewportSize(viewportSize());
    repositionSkillButtons();
    setupShader();
}

void TestGameButtonsApp::repositionSkillButtons()
{
    calculateButtonPositions();
    for (int i = 0; i < k_numSkillButtons; ++i)
    {
        SkillButton *button = widgets_.widget<SkillButton>(i+1);
        button->setPos(buttonPositions_[i][0], buttonPositions_[i][1]);
    }
}

} // end of namespace botlib
} // end of namespace mcdane
