#ifndef INCLUDED_BOTLIB_TEST_PARTICLE_APP_H
#define INCLUDED_BOTLIB_TEST_PARTICLE_APP_H

#include <commonlib_app.h>
#include <commonlib_random.h>
#include <commonlib_input_event.h>
#include <botlib_time_delta_smoother.h>
#include <botlib_update_context.h>
#include <botlib_game_map.h>

namespace mcdane {
namespace botlib {

class TestParticleApp: public commonlib::App {
public:
    TestParticleApp();

    ~TestParticleApp() override = default;

#ifdef DESKTOP_APP
    void init(const std::string &configFile,
              const std::string &appDir);
#elif __ANDROID__
    void init(android_app *app,
              const std::string &configFile);
#endif

    void process() override;

    bool operator()(const commonlib::InputEvent &e);

private:
    void setupGame();

    void setupDeltaSmoother();

    void setupUpdateContext();

    void setupTemplates();

    void setupMap();

    void setupInput();

    void addParticleEffects();

    void onViewportChange(float width, float height) override;

    void update();

    void present();

    void clearUpdateFlags();

    void updateObjs();

    void clearObjs();

#ifdef DESKTOP_APP
    void processMouseButton(const commonlib::MouseButtonEvent &e);
#endif

private:
    TimeDeltaSmoother deltaSmoother_;
    UpdateContext cxt_;
    GameMap map_;
    commonlib::Random rand_;
    std::vector<const ParticleEffectTemplate*> templates_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif
