#ifndef INCLUDED_BOTLIB_TEST_DIRECTION_PIE_APP_H
#define INCLUDED_BOTLIB_TEST_DIRECTION_PIE_APP_H

#include <commonlib_app.h>
#include <botlib_direction_pie.h>

namespace mcdane {
namespace botlib {

class TestDirectionPieApp: public commonlib::App {
public:
    TestDirectionPieApp() = default;

    ~TestDirectionPieApp() override = default;

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

    void setupDirectionPie();

    void setupInput();

    void onViewportChange(float width, float height) override;

    void onPointerDown(float x, float y);

    void onPointerOver(float x, float y);

private:
    DirectionPie pie_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif
