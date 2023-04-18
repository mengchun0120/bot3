#ifndef INCLUDED_BOTLIB_TEST_GAME_NAVIGATOR_APP_H
#define INCLUDED_BOTLIB_TEST_GAME_NAVIGATOR_APP_H

#include <commonlib_app.h>
#include <botlib_game_navigator.h>

namespace mcdane {
namespace botlib {

class TestGameNavigatorApp: public commonlib::App {
public:
    TestGameNavigatorApp() = default;

    ~TestGameNavigatorApp() override = default;

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

    void present();

    void setupShader();

    void setupNavigator();

    void setupInput();

    void onViewportChange(float width, float height) override;

    void calculateNavigatorPos(commonlib::Vector2 &p);

    void onSteer(const commonlib::Vector2 &direction);

    void resetNavigatorPos();

    void onPointerDown(float x, float y);

    void onPointerOver(float x, float y);

private:
    GameNavigator navigator_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif
