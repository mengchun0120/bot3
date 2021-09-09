#ifndef INCLUDED_TESTSHAPE_TESTSHAPE_H
#define INCLUDED_TESTSHAPE_TESTSHAPE_H

#include <commonlib_app.h>
#include <commonlib_texture.h>
#include <botlib_app_config.h>
#include <botlib_simple_shader_program.h>
#include <botlib_text_system.h>
#include <botlib_rectangle.h>

namespace mcdane {
namespace testshape {

class TestShapeApp: public commonlib::App {
public:
    TestShapeApp(const std::string& configFile,
                 const std::string& appDir);

    ~TestShapeApp() override = default;

    void preProcess() override;

    void process() override;

    void postProcess() override;

private:
    void setupOpenGL();

    void setupShapeColor();

    void setupTexture(const std::string& appDir);

private:
    botlib::AppConfig cfg_;
    botlib::SimpleShaderProgram program_;
    botlib::TextSystem textSys_;
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

} // end of namespace testshape
} // end of namespace mcdane

#endif
