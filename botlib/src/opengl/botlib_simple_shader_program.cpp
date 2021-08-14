#include <iostream>
#include <commonlib_file_utils.h>
#include <botlib_simple_shader_program.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void SimpleShaderProgram::init(const std::string& vertexShaderFile,
                               const std::string& fragShaderFile)
{
    std::string vertexShaderSrc = readTextFile(vertexShaderFile);
    std::string fragShaderSrc = readTextFile(fragShaderFile);

    load(vertexShaderSrc, fragShaderSrc);
    positionLocation_ = getAttribLocation("position");
    useObjRefLocation_ = getUniformLocation("useObjRef");
    objRefLocation_ = getUniformLocation("objRef");
    viewportSizeLocation_ = getUniformLocation("viewportSize");
    viewportOriginLocation_ = getUniformLocation("viewportOrigin");
    colorLocation_ = getUniformLocation("color");
    useColorLocation_ = getUniformLocation("useColor");
    texPosLocation_ = getAttribLocation("texPos");
    textureLocation_ = getUniformLocation("texture");
    useDirectionLocation_ = getUniformLocation("useDirection");
    directionLocation_ = getUniformLocation("direction");
    useTexColorLocation_ = getUniformLocation("useTexColor");
    texColorLocation_ = getUniformLocation("texColor");
}

} // end of namespace botlib
} // end of namespace mcdane

