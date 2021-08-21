#ifndef INCLUDED_TESTSHAPE_TESTSHAPE_H
#define INCLUDED_TESTSHAPE_TESTSHAPE_H

#include <commonlib_app.h>
#include <botlib_app_config.h>
#include <botlib_simple_shader_program.h>
#include <botlib_polygon.h>

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

private:
    botlib::AppConfig cfg_;
    botlib::SimpleShaderProgram program_;
    botlib::Polygon triangle_;
    botlib::Polygon square_;
    commonlib::Point2 trianglePos_;
    commonlib::Point2 squarePos_;
    commonlib::Color fillColor_;
    commonlib::Color borderColor_;
};

} // end of namespace testshape
} // end of namespace mcdane

#endif

