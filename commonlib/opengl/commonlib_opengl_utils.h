#ifndef INCLUDED_COMMONLIB_OPENGL_UTILS_H
#define INCLUDED_COMMONLIB_OPENGL_UTILS_H

#include <string>
#include <vector>
#include <initializer_list>
#include <commonlib_opengl.h>
#include <commonlib_vector.h>

namespace mcdane {
namespace commonlib {

void validateTexPos(const Point2 &texPos);

bool isShaderCompileSuccessful(GLuint shader);

bool compileShader(GLuint shader,
                   const std::string &path);

std::string getShaderInfo(GLuint shader);

std::string getShaderName(GLenum type);

GLuint createShader(GLenum type,
                    const std::string &fileName);

GLuint createShader(GLenum type,
                    std::initializer_list<std::string> fileNames);

GLuint createShader(GLenum type,
                    const std::vector<std::string> &fileNames);

bool isProgramLinkSuccessful(GLuint program);

bool linkProgram(GLuint program,
                 GLuint vertexShader,
                 GLuint fragShader);

std::string getProgramInfo(GLuint program);

GLuint createProgram(GLuint vertexShader,
                     GLuint fragShader);

void destroyShader(GLuint program,
                   GLuint shader);

void destroyProgram(GLuint program);

} // end of namespace commonlib
} // end of namespace mcdane

#endif
