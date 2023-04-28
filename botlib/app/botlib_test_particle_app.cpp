#include <commonlib_log.h>
#include <commonlib_input_manager.h>
#include <botlib_app_config.h>
#include <botlib_context.h>
#include <botlib_particle_effect.h>
#include <botlib_test_particle_app.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

TestParticleApp::TestParticleApp()
    : App()
{
}

#ifdef DESKTOP_APP
void TestParticleApp::init(const std::string &configFile,
                           const std::string &appDir)
{
    AppConfig::init(configFile, appDir);
    const AppConfig &cfg = AppConfig::instance();
    App::init(cfg.width(), cfg.height(), cfg.title());
    Context::init(cfg);
    setupGame();
}
#elif __ANDROID__
void TestParticleApp::init(android_app *app,
                           const std::string &configFile)
{
    AppConfig::init(configFile);
    App::init(app);
    const AppConfig &cfg = AppConfig::instance();
    Context::init(cfg);
    setupGame();
}
#endif

void TestParticleApp::process()
{
    App::process();

    InputManager::instance().processInput(*this);

    deltaSmoother_.update();
    cxt_.setTimeDelta(deltaSmoother_.curTimeDelta());

    update();
    present();
    clearObjs();

    postProcess();
}

#ifdef DESKTOP_APP
bool TestParticleApp::operator()(const InputEvent &e)
{
    switch (e.type())
    {
        case EventType::MOUSE_BUTTON:
            processMouseButton(e.mouseButtonEvent());
            break;
        default:
            break;
    }

    return true;
}
#elif __ANDROID__
bool TestParticleApp::operator()(const InputEvent &e)
{
    if (e.type_ == InputEvent::POINTER_DOWN)
    {
        addParticleEffects();
    }

    return true;
}
#endif

void TestParticleApp::setupGame()
{
    setupDeltaSmoother();
    setupUpdateContext();
    setupTemplates();
    setupMap();
    setupInput();
}

void TestParticleApp::setupDeltaSmoother()
{
    const AppConfig& cfg = AppConfig::instance();

    deltaSmoother_.init(cfg.timeDeltaHistoryLen());
    deltaSmoother_.start();
}

void TestParticleApp::setupUpdateContext()
{
    cxt_.init(&map_, 500, 500);
}

void TestParticleApp::setupTemplates()
{
    Context::gameLib().particleEffectTemplateLib().getAll(templates_);
}

void TestParticleApp::setupMap()
{
    map_.init(60, 60, viewportWidth(), viewportHeight(),
              cxt_.factory().deleter());
    addParticleEffects();
}

#ifdef DESKTOP_APP
void TestParticleApp::setupInput()
{
    const AppConfig &cfg = AppConfig::instance();
    InputManager::initInstance(window(), viewportSize(),
                               cfg.inputQueueCapacity());
    InputManager::instance().enable();
}
#elif __ANDROID__
void TestParticleApp::setupInput()
{
    InputManager::initInstance(app_, viewportSize());
}
#endif

void TestParticleApp::addParticleEffects()
{
    Vector2 pos;
    const ParticleEffectTemplate *t;

    for (int i = 0; i < 3; ++i)
    {
        pos[0] = rand_.randomFloat(0.0f, viewportWidth());
        pos[1] = rand_.randomFloat(0.0f, viewportHeight());
        t = templates_[rand_.randomInt(0, templates_.size()-1)];
        ParticleEffect *effect = cxt_.factory().createParticleEffect(t, pos);
        map_.addObj(effect);
    }
}

void TestParticleApp::onViewportChange(float width, float height)
{
    App::onViewportChange(width, height);
    InputManager::instance().setViewportSize(viewportSize());
    map_.resetViewport(viewportWidth(), viewportHeight());
}

void TestParticleApp::update()
{
    clearUpdateFlags();
    updateObjs();
}

void TestParticleApp::present()
{
    glClear(GL_COLOR_BUFFER_BIT);
    map_.present();
    glFlush();
}

void TestParticleApp::clearUpdateFlags()
{
    auto clearUpdateFlag = [](GameObject *obj)->bool
    {
        obj->setUpdated(false);
        return true;
    };

    map_.traverse(map_.presentArea(), clearUpdateFlag);
}

void TestParticleApp::updateObjs()
{
    auto updater = [this](GameObject *obj)->bool
    {
        if (obj->updated() && obj->state() == GameObjectState::DEAD)
        {
            return true;
        }

        obj->update(cxt_);
        return true;
    };

    map_.traverse(map_.presentArea(), updater);
}

void TestParticleApp::clearObjs()
{
    if (!cxt_.dumper().empty())
    {
        cxt_.dumper().clear(map_);
    }
}

#ifdef DESKTOP_APP
void TestParticleApp::processMouseButton(const MouseButtonEvent &e)
{
    if (e.button_ != GLFW_MOUSE_BUTTON_LEFT || e.action_ != GLFW_PRESS)
    {
        return;
    }

    addParticleEffects();
}
#endif

} // end of namespace botlib
} // end of namespace mcdane
