#include <iostream>
#include <commonlib_exception.h>
#include <commonlib_opengl_utils.h>
#include <commonlib_shader_program.h>

namespace mcdane {
namespace commonlib {

ShaderProgram::ShaderProgram():
    vertexShader_(0),
    fragShader_(0),
    program_(0)
{
}

ShaderProgram::ShaderProgram(const std::string& vertexShaderSrc,
                             const std::string& fragShaderSrc):
    ShaderProgram()
{
    load(vertexShaderSrc, fragShaderSrc);
}

ShaderProgram::~ShaderProgram()
{
    destroyShader(program_, vertexShader_);
    destroyShader(program_, fragShader_);
    destroyProgram(program_);
}

void ShaderProgram::load(const std::string& vertexShaderSrc,
                         const std::string& fragShaderSrc)
{
    vertexShader_ = createShader(GL_VERTEX_SHADER, vertexShaderSrc);
    fragShader_ = createShader(GL_FRAGMENT_SHADER, fragShaderSrc);
    program_ = createProgram(vertexShader_, fragShader_);
}

void ShaderProgram::use()
{
    glUseProgram(program_);
}

GLint ShaderProgram::getUniformLocation(const char* name)
{
    GLint loc = glGetUniformLocation(program_, name);
    if (loc < 0)
    {
        THROW_EXCEPT(OpenGLException,
                     std::string("glGetUniformLocation failed: name=") + name +
                     " error=" + getError());
    }

    return loc;
}

GLint ShaderProgram::getAttribLocation(const char* name)
{
    GLint loc = glGetAttribLocation(program_, name);
    if (loc < 0)
    {
        THROW_EXCEPT(OpenGLException,
                     std::string("glGetAttribLocation failed: name=") + name +
                     " error=" + getError());
    }

    return loc;
}

const std::string ShaderProgram::getError() const
{
    GLint err = glGetError();
    switch(err)
    {
        case GL_NO_ERROR:
            return "GL_NO_ERROR";
        case GL_INVALID_ENUM:
            return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE:
            return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION:
            return "GL_INVALID_OPERATION";
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "GL_INVALID_FRAMEBUFFER_OPERATION";
        case GL_OUT_OF_MEMORY:
            return "GL_OUT_OF_MEMORY";
        case GL_STACK_UNDERFLOW:
            return "GL_STACK_UNDERFLOW";
        case GL_STACK_OVERFLOW:
            return "GL_STACK_OVERFLOW";
    }

    return "Unknow error " + std::to_string(err);
}

} // end of namespace commonlib
} // end of namespace mcdane

