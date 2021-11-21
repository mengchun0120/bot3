#ifndef INCLUDE_COMMONLIB_SHADER_PROGRAM_H
#define INCLUDE_COMMONLIB_SHADER_PROGRAM_H

#include <initializer_list>
#include <string>
#include <commonlib_opengl.h>

namespace mcdane {
namespace commonlib {

class ShaderProgram {
public:
    ShaderProgram();

    ShaderProgram(std::initializer_list<std::string> vertexShaderFiles,
                  std::initializer_list<std::string> fragShaderFiles);

    ShaderProgram(const std::vector<std::string>& vertexShaderFiles,
                  const std::vector<std::string>& fragShaderFiles);

    ShaderProgram(const ShaderProgram& other) = delete;

    virtual ~ShaderProgram();

    void load(std::initializer_list<std::string> vertexShaderFiles,
              std::initializer_list<std::string> fragShaderFiles);

    void load(const std::vector<std::string>& vertexShaderFiles,
              const std::vector<std::string>& fragShaderFiles);

    bool valid() const noexcept
    {
        return vertexShader_ != 0 &&
               fragShader_ != 0 &&
               program_ != 0;
    }

    ShaderProgram& operator=(const ShaderProgram& other) = delete;

    void use();

    GLint getUniformLocation(const char* name);

    GLint getAttribLocation(const char* name);

    const std::string getError() const;

    GLuint program() const
    {
        return program_;
    }

private:
    GLuint vertexShader_;
    GLuint fragShader_;
    GLuint program_;
};

} // end of namespace commonlib
} // end of namespace mcdane

#endif
