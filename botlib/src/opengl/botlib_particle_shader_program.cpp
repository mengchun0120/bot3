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

void ParticleShaderProgram::setDirection(const commonlib::VertexArray& va)
{
    if (va.numBufferBlocks() == 0)
    {
        THROW_EXCEPT(OpenGLException, "VertexArray contains zero buffer block");
    }

    glBindVertexArray(va.arrayObj());
    glBindBuffer(GL_ARRAY_BUFFER, va.bufferObj());

    glVertexAttribPointer(directionLoc_,
                          Constants::FLOATS_PER_POS,
                          GL_FLOAT,
                          GL_FALSE,
                          va.stride(0),
                          reinterpret_cast<void *>(0));

    glEnableVertexAttribArray(directionLoc_);
}

void ParticleShaderProgram::setTexture(GLuint textureId)
{
}

void ParticleShaderProgram::initLocations()
{
    viewportSizeLoc_ = getUniformLocation("viewportSize");
    viewportOriginLoc_ = getUniformLocation("viewportOrigin");
    refLoc_ = getUniformLocation("ref");
    curTimeLoc_ = getUniformLocation("curTime");
    accelerationLoc_ = getUniformLocation("acceleration");
    initSpeedLoc_ = getUniformLocation("initSpeed");
    particleSizeLoc_ = getUniformLocation("particleSize");
    colorLoc_ = getUniformLocation("color");
    textureLoc_ = getUniformLocation("texture");
    directionLoc_ = getAttribLocation("direction");
}

} // end of namespace botlib
} // end of namespace mcdane

