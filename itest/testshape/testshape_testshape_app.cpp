#include <testshape_testshape_app.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace testshape {

TestShapeApp::TestShapeApp(const std::string& configFile,
                           const std::string& appDir)
{
    cfg_.load(configFile, appDir);
#ifdef DESKTOP_APP
    setupWindow(1000, 800, "Test Shape");
#endif

    setupOpenGL();
    setupShapeColor();
}

void TestShapeApp::setupOpenGL()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    Point2 viewportOrigin{viewportWidth() / 2.0f, viewportHeight() / 2.0f};

    program_.init(cfg_.simpleVertexShaderFile(),
                 cfg_.simpleFragShaderFile());
    program_.use();
    program_.setViewportSize(viewportSize());
    program_.setViewportOrigin(viewportOrigin);
}

void TestShapeApp::setupShapeColor()
{
    triangle_.load({
        Point3{0.0f, 0.0f, 0.0f},
        Point3{0.0f, 100.0f, 0.0f},
        Point3{-100.0f, -50.0f, 0.0f},
        Point3{100.0f, -50.0f, 0.0f},
        Point3{0.0f, 100.0f, 0.0f}
    });

    square_.load({
        Point3{0.0f, 0.0f, 0.0f},
        Point3{-100.0f, 100.0f, 0.0f},
        Point3{-100.0f, -100.0f, 0.0f},
        Point3{100.0f, -100.0f, 0.0f},
        Point3{100.0f, 100.0f, 0.0f},
        Point3{-100.0f, 100.0f, 0.0f}
    });

    trianglePos_.init({200.0f, 200.0f});
    squarePos_.init({600.0f, 400.0f});

    fillColor_.init({1.0f, 0.5f, 0.0f, 1.0f});
    borderColor_.init({0.0f, 0.0f, 0.3f, 1.0f});
}

void TestShapeApp::preProcess()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void TestShapeApp::process()
{
    triangle_.draw(program_, &trianglePos_, nullptr, &fillColor_,
                   nullptr, 0, nullptr);
    square_.draw(program_, &squarePos_, nullptr, &fillColor_,
                 &borderColor_, 0, nullptr);
}

void TestShapeApp::postProcess()
{
    App::postProcess();
}

} // end of namespace testshape
} // end of namespace mcdane

