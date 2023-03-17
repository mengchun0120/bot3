#include <commonlib_exception.h>
#include <commonlib_log.h>
#include <commonlib_file_utils.h>
#include <commonlib_opengl_utils.h>

namespace mcdane {
namespace commonlib {

void validateTexPos(const Point2 &texPos)
{
    if (texPos[0] < 0.0f || texPos[0] > 1.0f)
    {
        THROW_EXCEPT(InvalidArgumentException, "texPos[0] is out of bound");
    }

    if (texPos[1] < 0.0f || texPos[1] > 1.0f)
    {
        THROW_EXCEPT(InvalidArgumentException, "texPos[1] is out of bound");
    }
}

bool isShaderCompileSuccessful(GLuint shader)
{
    GLint compileStatus;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
    return compileStatus != 0;
}

bool compileShader(GLuint shader,
                   const std::string &path)
{
    std::string src = readText(path);

    const GLchar *source = src.c_str();
    GLint len = src.length();

    glShaderSource(shader, 1, static_cast<const GLchar * const*>(&source), &len);
    glCompileShader(shader);

    bool result = isShaderCompileSuccessful(shader);

    LOG_INFO << "Compilation  " << (result ? "successful" : "failed") << LOG_END;

    return result;
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

std::string getShaderName(GLenum type)
{
    switch (type)
    {
        case GL_VERTEX_SHADER:
            return "vertex shader";
        case GL_FRAGMENT_SHADER:
            return "fragment shader";
    }

    return "unknown shader";
}

GLuint createShader(GLenum type,
                    const std::string &fileName)
{
    return createShader(type, {fileName});
}

GLuint createShader(GLenum type,
                    std::initializer_list<std::string> fileNames)
{
    return createShader(type, std::vector<std::string>(fileNames));
}

GLuint createShader(GLenum type,
                    const std::vector<std::string> &fileNames)
{
    GLuint shader = glCreateShader(type);
    if (shader == 0)
    {
        THROW_EXCEPT(OpenGLException, "glCreateShader failed");
    }

    auto it = fileNames.begin();
    for (; it != fileNames.end(); ++it)
    {
        LOG_INFO << "Compiling " << getShaderName(type) << " from "
                 << *it << LOG_END;

        if (compileShader(shader, *it))
        {
            break;
        }
    }

    if (it == fileNames.end())
    {
        THROW_EXCEPT(OpenGLException,
                     "Failed to compile " + getShaderName(type) +
                     ": " + getShaderInfo(shader));
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

} // end of namespace commonlib
} // end of namespace mcdane
