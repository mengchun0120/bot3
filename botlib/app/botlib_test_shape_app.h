#ifndef INCLUDED_BOTLIB_TEST_SHAPE_APP_H
#define INCLUDED_BOTLIB_TEST_SHAPE_APP_H

#include <commonlib_app.h>
#include <commonlib_color.h>
#include <commonlib_texture.h>
#include <botlib_rectangle.h>

namespace mcdane {
namespace botlib {

class TestShapeApp: public commonlib::App {
public:
    TestShapeApp();

#ifdef DESKTOP_APP
    void init(const std::string& configFile,
              const std::string& appDir);
#elif __ANDROID__
    void init(android_app *app);
#endif

    ~TestShapeApp() override = default;

    void process() override;

protected:
    void setupShader();

    void setupShapeColor();

    void setupTexture();

    void onViewportChange(float width1, float height1) override;

private:
    botlib::Polygon triangle_;
    botlib::Rectangle square_;
    commonlib::Point2 trianglePos_;
    commonlib::Point2 squarePos_;
    commonlib::Color fillColor_;
    commonlib::Color borderColor_;
    commonlib::Texture texture_;
    botlib::Rectangle texRect_;
    commonlib::Point2 texPos_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

