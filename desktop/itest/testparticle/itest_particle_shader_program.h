#ifndef INCLUDED_ITEST_PARTICLE_SHADER_PROGRAM_H
#define INCLUDED_ITEST_PARTICLE_SHADER_PROGRAM_H

#include <commonlib_vertex_array.h>
#include <commonlib_color.h>
#include <commonlib_shader_program.h>

namespace mcdane {
namespace itest {

class ParticleShaderProgram: public commonlib::ShaderProgram {
public:
    void load(const std::string& vertexShaderFile,
              const std::string& fragShaderFile);

    inline void setViewportOrigin(const commonlib::Vector2& origin);

    inline void setViewportSize(const commonlib::Vector2& size);

    inline void setCurTime(float curTime);

    inline void setAcceleration(float acceleration);

    inline void setPointSize(float pointSize);

    inline void setColor(const commonlib::Color& color);

    inline void setDuration(float duration);

    void setStartPosDirectionSpeed(const commonlib::VertexArray& va);

    void setPointTexture(GLuint textureId);

private:
    GLint viewportOriginLoc_;
    GLint viewportSizeLoc_;
    GLint curTimeLoc_;
    GLint accelerationLoc_;
    GLint startPosLoc_;
    GLint directionLoc_;
    GLint initSpeedLoc_;
    GLint pointSizeLoc_;
    GLint colorLoc_;
    GLint durationLoc_;
    GLint pointTextureLoc_;
};

void ParticleShaderProgram::setViewportOrigin(const commonlib::Vector2& origin)
{
    glUniform2fv(viewportOriginLoc_, 1, reinterpret_cast<const GLfloat *>(&origin));
}

void ParticleShaderProgram::setViewportSize(const commonlib::Vector2& size)
{
    glUniform2fv(viewportSizeLoc_, 1, reinterpret_cast<const GLfloat *>(&size));
}

void ParticleShaderProgram::setCurTime(float curTime)
{
    glUniform1f(curTimeLoc_, curTime);
}

void ParticleShaderProgram::setAcceleration(float acceleration)
{
    glUniform1f(accelerationLoc_, acceleration);
}

void ParticleShaderProgram::setPointSize(float pointSize)
{
    glUniform1f(pointSizeLoc_, pointSize);
}

void ParticleShaderProgram::setColor(const commonlib::Color& color)
{
    glUniform4fv(colorLoc_, 1, reinterpret_cast<const GLfloat*>(&color));
}

void ParticleShaderProgram::setDuration(float duration)
{
    glUniform1f(durationLoc_, duration);
}

} // end of namespace itest
} // end of namespace mcdane

#endif

