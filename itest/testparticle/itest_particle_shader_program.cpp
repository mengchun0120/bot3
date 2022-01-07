#include <botlib_constants.h>
#include <itest_particle_shader_program.h>

using namespace mcdane::commonlib;
using namespace mcdane::botlib;

namespace mcdane {
namespace itest {

void ParticleShaderProgram::load(const std::string& vertexShaderFile,
                                 const std::string& fragShaderFile)
{
    ShaderProgram::load({vertexShaderFile}, {fragShaderFile});
    viewportOriginLoc_ = getUniformLocation("viewportOrigin");
    viewportSizeLoc_ = getUniformLocation("viewportSize");
    curTimeLoc_ = getUniformLocation("curTime");
    accelerationLoc_ = getUniformLocation("acceleration");
    startPosLoc_ = getAttribLocation("startPos");
    directionLoc_ = getAttribLocation("direction");
    initSpeedLoc_ = getAttribLocation("initSpeed");
    pointSizeLoc_ = getUniformLocation("pointSize");
    colorLoc_ = getUniformLocation("color");
    durationLoc_ = getUniformLocation("duration");
    pointTextureLoc_ = getUniformLocation("pointTexture");
}

void ParticleShaderProgram::setStartPosDirectionSpeed(
                                            const commonlib::VertexArray& va)
{
    glBindVertexArray(va.arrayObj());
    glBindBuffer(GL_ARRAY_BUFFER, va.bufferObj());

    glVertexAttribPointer(startPosLoc_, Constants::FLOATS_PER_POS,
                          GL_FLOAT, GL_FALSE,
                          va.stride(0), reinterpret_cast<void *>(0));
    glEnableVertexAttribArray(startPosLoc_);


    glVertexAttribPointer(directionLoc_, Constants::FLOATS_PER_POS,
                          GL_FLOAT, GL_FALSE,
                          va.stride(1), reinterpret_cast<void *>(va.offset(1)));
    glEnableVertexAttribArray(directionLoc_);

    glVertexAttribPointer(initSpeedLoc_, 1, GL_FLOAT, GL_FALSE,
                          va.stride(2), reinterpret_cast<void *>(va.offset(2)));
    glEnableVertexAttribArray(initSpeedLoc_);
}

void ParticleShaderProgram::setPointTexture(GLuint textureId)
{
    glUniform1i(pointTextureLoc_, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
}

} // end of namespace itest
} // end of namespace mcdane

