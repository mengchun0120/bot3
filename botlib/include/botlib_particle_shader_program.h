#ifndef INCLUDED_BOTLIB_PARTICLE_SHADER_PROGRAM_H
#define INCLUDED_BOTLIB_PARTICLE_SHADER_PROGRAM_H

#include <commonlib_vector.h>
#include <commonlib_color.h>
#include <commonlib_vertex_array.h>
#include <commonlib_shader_program.h>

namespace mcdane {
namespace botlib {

class ParticleShaderProgram: public commonlib::ShaderProgram {
public:
    ParticleShaderProgram() = default;

    ~ParticleShaderProgram() override = default;

    void init(const std::vector<std::string>& vertexShaderFiles,
              const std::vector<std::string>& fragShaderFiles);

    inline void setViewportSize(const commonlib::Vector2& viewportSize);

    inline void setViewportOrigin(const commonlib::Vector2& viewportOrigin);

    inline void setRef(const commonlib::Vector2& ref);

    inline void setCurTime(float curTime);

    inline void setAcceleration(float acceleration);

    inline void setParticleSize(float particleSize);

    inline void setColor(const commonlib::Color& color);

    void setStartPosDirectionSpeed(const commonlib::VertexArray& va);

    void setTexture(GLuint textureId);

private:
    void initLocations();

private:
    GLint viewportSizeLoc_;
    GLint viewportOriginLoc_;
    GLint refLoc_;
    GLint curTimeLoc_;
    GLint accelerationLoc_;
    GLint particleSizeLoc_;
    GLint startPosLoc_;
    GLint directionLoc_;
    GLint initSpeedLoc_;
    GLint textureLoc_;
    GLint colorLoc_;
};

void ParticleShaderProgram::setViewportSize(
                                    const commonlib::Vector2& viewportSize)
{
    glUniform2fv(viewportSizeLoc_, 1,
                 reinterpret_cast<const GLfloat*>(&viewportSize));
}

void ParticleShaderProgram::setViewportOrigin(
                                    const commonlib::Vector2& viewportOrigin)
{
    glUniform2fv(viewportOriginLoc_, 1,
                 reinterpret_cast<const GLfloat*>(&viewportOrigin));
}

void ParticleShaderProgram::setRef(const commonlib::Vector2& ref)
{
    glUniform2fv(refLoc_, 1, reinterpret_cast<const GLfloat*>(&ref));
}

void ParticleShaderProgram::setCurTime(float curTime)
{
    glUniform1f(curTimeLoc_, curTime);
}

void ParticleShaderProgram::setAcceleration(float acceleration)
{
    glUniform1f(accelerationLoc_, acceleration);
}

void ParticleShaderProgram::setParticleSize(float particleSize)
{
    glUniform1f(particleSizeLoc_, particleSize);
}

void ParticleShaderProgram::setColor(const commonlib::Color& color)
{
    glUniform4fv(colorLoc_, 1, reinterpret_cast<const GLfloat*>(&color));
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
