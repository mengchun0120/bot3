#ifndef INCLUDED_BOTLIB_SIMPLE_SHADER_PROGRAM_H
#define INCLUDED_BOTLIB_SIMPLE_SHADER_PROGRAM_H

#include <commonlib_shader_program.h>

namespace mcdane {
namespace botlib {

class SimpleShaderProgram: public commonlib::ShaderProgram {
public:
    SimpleShaderProgram() = default;

    ~SimpleShaderProgram() override = default;

    void init(const std::string& vertexShaderFile,
              const std::string& fragShaderFile);

private:
    GLint positionLocation_;
    GLint useObjRefLocation_;
    GLint objRefLocation_;
    GLint viewportSizeLocation_;
    GLint viewportOriginLocation_;
    GLint colorLocation_;
    GLint useColorLocation_;
    GLint texPosLocation_;
    GLint textureLocation_;
    GLint useDirectionLocation_;
    GLint directionLocation_;
    GLint useTexColorLocation_;
    GLint texColorLocation_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

