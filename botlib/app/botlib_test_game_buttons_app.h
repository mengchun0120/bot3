#ifndef INCLUDED_BOTLIB_TEST_GAME_BUTTONS_APP_H
#define INCLUDED_BOTLIB_TEST_GAME_BUTTONS_APP_H

#include <commonlib_app.h>
#include <botlib_time_delta_smoother.h>
#include <botlib_widget_group.h>

namespace mcdane {
namespace botlib {

class TestGameButtonsApp: public commonlib::App {

    static constexpr int k_numSkillButtons = 3;

public:
    TestGameButtonsApp() = default;

    ~TestGameButtonsApp() override = default;

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
    void setup();

    void update(float timeDelta);

    void present();

    void setupShader();

    void setupCoolDownDurations();

    void setupWidgets();

    void setupDeltaSmoother();

    void setupInput();

    void setupSkillButtons();

    void addSkillButton(int idx,
                        float x,
                        float y,
                        const std::string &pieTemplate,
                        const std::string &actionMsg);

    void calculateButtonPositions();

    void onViewportChange(float width, float height) override;

    void repositionSkillButtons();

private:
    TimeDeltaSmoother deltaSmoother_;
    WidgetGroup widgets_;
    std::vector<commonlib::Vector2> buttonPositions_;
    std::vector<float> coolDowns_;
    std::vector<float> durations_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif
