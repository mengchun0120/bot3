#include <iostream>
#include <commonlib_exception.h>
#include <commonlib_shader_program.h>

namespace mcdane {
namespace commonlib {

bool isShaderCompileSuccessful(GLuint shader)
{
    GLint compileStatus;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
    return compileStatus != 0;
}

bool compileShader(GLuint shader,
                   const std::string& src)
{
    const GLchar* source = src.c_str();
    GLint len = src.length();

    glShaderSource(shader, 1, static_cast<const GLchar * const*>(&source), &len);
    glCompileShader(shader);

    return isShaderCompileSuccessful(shader);
}

std::string getShaderInfo(GLuint shader)
{
    GLint infoLen;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

    char *info = new char[infoLen + 1];
    glGetShaderInfoLog(shader, infoLen, NULL, info);

    std::string msg(info);

    delete[] info;

    return msg;
}

GLuint createShader(GLenum type,
                    const std::string& src)
{
    GLuint shader = glCreateShader(type);
    if (shader == 0)
    {
        THROW_EXCEPT(OpenGLException, "glCreateShader failed");
    }

    if (!compileShader(shader, src))
    {
        THROW_EXCEPT(OpenGLException,
                     "Failed to compile shader: " + getShaderInfo(shader));
    }

    return shader;
}

bool isProgramLinkSuccessful(GLuint program)
{
    GLint linkStatus;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
    return linkStatus != 0;
}

bool linkProgram(GLuint program,
                 GLuint vertexShader,
                 GLuint fragShader)
{
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);
    return isProgramLinkSuccessful(program);
}

std::string getProgramInfo(GLuint program)
{
    GLint infoLen;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);

    char *info = new char[infoLen + 1];
    glGetProgramInfoLog(program, infoLen, NULL, info);

    std::string msg(info);

    delete[] info;

    return msg;
}

GLuint createProgram(GLuint vertexShader,
                     GLuint fragShader)
{
    GLuint program = glCreateProgram();
    if (program == 0)
    {
        THROW_EXCEPT(OpenGLException, "glCreateProgram failed");
    }

    if (!linkProgram(program, vertexShader, fragShader))
    {
        THROW_EXCEPT(OpenGLException,
                     "Failed to link program: " + getProgramInfo(program));
    }

    return program;
}

void destroyShader(GLuint program,
                   GLuint shader)
{
    if (program != 0 && shader != 0)
    {
        glDetachShader(program, shader);
        glDeleteShader(shader);
    }
}

void destroyProgram(GLuint program)
{
    if (program != 0)
    {
        glDeleteProgram(program);
    }
}

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

