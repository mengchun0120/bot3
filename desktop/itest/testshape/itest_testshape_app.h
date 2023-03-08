#ifndef INCLUDED_ITEST_TESTSHAPE_APP_H
#define INCLUDED_ITEST_TESTSHAPE_APP_H

#include <commonlib_app.h>
#include <commonlib_texture.h>
#include <botlib_rectangle.h>

namespace mcdane {
namespace itest {

class TestShapeApp: public commonlib::App {
public:
    TestShapeApp(const std::string& configFile,
                 const std::string& appDir);

    ~TestShapeApp() override = default;

    void process() override;

protected:
    void setupShader();

    void setupShapeColor();

    void setupTexture(const std::string& appDir);

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

} // end of namespace itest
} // end of namespace mcdane

#endif
