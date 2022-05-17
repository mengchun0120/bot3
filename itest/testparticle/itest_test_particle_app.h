#ifndef INCLUDED_ITEST_TEST_PARTICLE_APP_H
#define INCLUDED_ITEST_TEST_PARTICLE_APP_H

#include <commonlib_app.h>
#include <commonlib_time_utils.h>
#include <commonlib_texture.h>
#include <itest_particle_shader_program.h>

namespace mcdane {
namespace itest {

class TestParticleApp: public commonlib::App {
public:
    TestParticleApp(const std::string& vertexShaderFile,
                    const std::string& fragShaderFile,
                    const std::string& textureFile);

    void process() override;

private:
    void setupOpenGL(const std::string& vertexShaderFile,
                     const std::string& fragShaderFile);

    void setupVA();

private:
    ParticleShaderProgram program_;
    commonlib::Color color_;
    commonlib::VertexArray va_;
    commonlib::TimePoint startTime_;
    commonlib::Texture texture_;
};

} // end of namespace itest
} // end of namespace mcdane

#endif

