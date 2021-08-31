#include <vector>
#include <commonlib_file_utils.h>
#include <testshape_testshape_app.h>

using namespace mcdane::commonlib;
using namespace mcdane::botlib;

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
    setupTexture(appDir);
}

void TestShapeApp::setupOpenGL()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Point2 viewportOrigin{viewportWidth() / 2.0f, viewportHeight() / 2.0f};

    program_.init(cfg_.simpleVertexShaderFile(),
                 cfg_.simpleFragShaderFile());
    program_.use();
    program_.setViewportSize(viewportSize());
    program_.setViewportOrigin(viewportOrigin);

    textSys_.load(cfg_.fontDir());
}

void TestShapeApp::setupShapeColor()
{
    triangle_.load({
        Point2{0.0f, 0.0f},
        Point2{0.0f, 100.0f},
        Point2{-100.0f, -50.0f},
        Point2{100.0f, -50.0f},
        Point2{0.0f, 100.0f}
    });

    square_.load(100.0f, 100.0f);

    trianglePos_.init({200.0f, 200.0f});
    squarePos_.init({600.0f, 400.0f});

    fillColor_.init({1.0f, 0.5f, 0.0f, 1.0f});
    borderColor_.init({0.0f, 0.0f, 0.3f, 1.0f});
}

void TestShapeApp::setupTexture(const std::string& appDir)
{
    std::string imageFile = constructPath(appDir,
                                          {"itest", "testshape", "baby.png"});
    texture_.init(imageFile);

    float w = static_cast<float>(texture_.width()) / 4.0f;

    texRect_.load(100.0f, 100.0f, TexRectangle());
    texPos_.init({w, 500.0});
}

void TestShapeApp::preProcess()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void TestShapeApp::process()
{
    triangle_.draw(program_, 0.0f, &trianglePos_, nullptr, &fillColor_,
                   nullptr, 0, nullptr);
    square_.draw(program_, 0.0f, &squarePos_, nullptr, &fillColor_,
                 &borderColor_, 0, nullptr);
    texRect_.draw(program_, 0.0f, &texPos_, nullptr, nullptr,
                  nullptr, texture_.id(), nullptr);
    textSys_.draw(program_, "Hello world", Point2{200.0f, 700.0f},
                  0.0f, TEXT_SIZE_BIG, &fillColor_);
    textSys_.draw(program_, "Hello world", Point2{200.0f, 600.0f},
                  0.0f, TEXT_SIZE_MEDIUM, &fillColor_);
    textSys_.draw(program_, "Hello world", Point2{200.0f, 500.0f},
                  0.0f, TEXT_SIZE_SMALL, &fillColor_);
    textSys_.draw(program_, "Hello world", Point2{200.0f, 400.0f},
                  0.0f, TEXT_SIZE_TINY, &fillColor_);
}

void TestShapeApp::postProcess()
{
    App::postProcess();
}

} // end of namespace testshape
} // end of namespace mcdane

