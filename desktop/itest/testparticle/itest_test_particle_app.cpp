#include <commonlib_log.h>
#include <commonlib_vector.h>
#include <botlib_constants.h>
#include <itest_test_particle_app.h>

using namespace mcdane::commonlib;
using namespace mcdane::botlib;

namespace mcdane {
namespace itest {

TestParticleApp::TestParticleApp(const std::string& vertexShaderFile,
                                 const std::string& fragShaderFile,
                                 const std::string& textureFile)
    : color_{255, 0, 0, 255}
{
    setupWindow(1000, 1000, "test particle");
    setupOpenGL(vertexShaderFile, fragShaderFile);
    setupVA();
    texture_.init(textureFile);
    startTime_ = Clock::now();
}

void TestParticleApp::process()
{
    glClear(GL_COLOR_BUFFER_BIT);

    program_.use();
    program_.setViewportOrigin(Vector2{500.0f, 500.0f});
    program_.setViewportSize(viewportSize());
    program_.setStartPosDirectionSpeed(va_);
    program_.setAcceleration(0.000025f);
    program_.setCurTime(elapsedTimeMs(startTime_));
    program_.setPointSize(20.0f);
    program_.setColor(color_);
    program_.setDuration(2000.0f);
    program_.setPointTexture(texture_.id());
    glDrawArrays(GL_POINTS, 0, va_.numVertices(0));
    glFlush();

    postProcess();
}

void TestParticleApp::setupOpenGL(const std::string& vertexShaderFile,
                                  const std::string& fragShaderFile)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_BLEND);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    program_.load(vertexShaderFile, fragShaderFile);
}

void TestParticleApp::setupVA()
{
    Vector2 startPos[] = {
        Vector2{500.0f, 500.0f},
        Vector2{600.0f, 500.0f}
    };

    Vector2 direction[] = {
        Vector2{0.0f, 1.0f},
        Vector2{1.0f, 0.0f}
    };

    float initSpeed[] = {
        0.05, 0.05
    };

    va_.load({
        BufferBlock(startPos, 2, Constants::POS_SIZE, 0),
        BufferBlock(direction, 2, Constants::POS_SIZE, 0),
        BufferBlock(initSpeed, 2, sizeof(float), 0)
    });
}

} // end of namespace itest
} // end of namespace mcdane

