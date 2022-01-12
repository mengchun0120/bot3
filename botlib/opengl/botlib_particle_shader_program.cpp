#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <botlib_constants.h>
#include <botlib_particle_shader_program.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void ParticleShaderProgram::init(const std::vector<std::string>& vertexShaderFiles,
                                 const std::vector<std::string>& fragShaderFiles)
{
    load(vertexShaderFiles, fragShaderFiles);
    initLocations();

    LOG_INFO << "ParticleShaderProgram initialized" << LOG_END;
}

void ParticleShaderProgram::setStartPosDirectionSpeed(const VertexArray& va)
{
    if (va.numBufferBlocks() != 3)
    {
        THROW_EXCEPT(OpenGLException, "Invalid VertexArray");
    }

    glBindVertexArray(va.arrayObj());
    glBindBuffer(GL_ARRAY_BUFFER, va.bufferObj());

    glVertexAttribPointer(startPosLoc_,
                          Constants::FLOATS_PER_POS,
                          GL_FLOAT,
                          GL_FALSE,
                          va.stride(0),
                          reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(startPosLoc_);

    glVertexAttribPointer(directionLoc_,
                          Constants::FLOATS_PER_DIRECTION,
                          GL_FLOAT,
                          GL_FALSE,
                          va.stride(1),
                          reinterpret_cast<void*>(va.offset(1)));
    glEnableVertexAttribArray(directionLoc_);

    glVertexAttribPointer(initSpeedLoc_, 1, GL_FLOAT, GL_FALSE,
                          va.stride(2), reinterpret_cast<void*>(va.offset(2)));
    glEnableVertexAttribArray(initSpeedLoc_);
}

void ParticleShaderProgram::setPointTexture(GLuint textureId)
{
    glUniform1i(pointTextureLoc_, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
}

void ParticleShaderProgram::initLocations()
{
    viewportSizeLoc_ = getUniformLocation("viewportSize");
    viewportOriginLoc_ = getUniformLocation("viewportOrigin");
    refLoc_ = getUniformLocation("ref");
    curTimeLoc_ = getUniformLocation("curTime");
    accelerationLoc_ = getUniformLocation("acceleration");
    particleSizeLoc_ = getUniformLocation("particleSize");
    durationLoc_ = getUniformLocation("duration");
    startPosLoc_ = getAttribLocation("startPos");
    directionLoc_ = getAttribLocation("direction");
    initSpeedLoc_ = getAttribLocation("initSpeed");
    colorLoc_ = getUniformLocation("color");
    pointTextureLoc_ = getUniformLocation("pointTexture");
}

} // end of namespace botlib
} // end of namespace mcdane

