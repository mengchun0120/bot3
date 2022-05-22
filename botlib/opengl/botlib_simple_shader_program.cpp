#include <commonlib_log.h>
#include <commonlib_file_utils.h>
#include <commonlib_exception.h>
#include <botlib_constants.h>
#include <botlib_simple_shader_program.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void SimpleShaderProgram::init(const std::vector<std::string>& vertexShaderFiles,
                               const std::vector<std::string>& fragShaderFiles)
{
    load(vertexShaderFiles, fragShaderFiles);
    initLocations();

    LOG_INFO << "SimpleShaderProgram initialized" << LOG_END;
}

void SimpleShaderProgram::setPositionTexPos(const VertexArray& va)
{
    if (va.numBufferBlocks() == 0)
    {
        THROW_EXCEPT(OpenGLException, "VertexArray contains zero buffer block");
    }

    glBindVertexArray(va.arrayObj());
    glBindBuffer(GL_ARRAY_BUFFER, va.bufferObj());

    glVertexAttribPointer(positionLoc_, Constants::FLOATS_PER_POS,
                          GL_FLOAT, GL_FALSE,
                          va.stride(0), reinterpret_cast<void *>(0));
    glEnableVertexAttribArray(positionLoc_);

    if (va.numBufferBlocks() > 1)
    {
        glVertexAttribPointer(texPosLoc_, Constants::FLOATS_PER_TEXPOS,
                              GL_FLOAT, GL_FALSE,
                              va.stride(1),
                              reinterpret_cast<void *>(va.offset(1)));
        glEnableVertexAttribArray(texPosLoc_);
    }
}

void SimpleShaderProgram::setTexture(GLuint textureId)
{
    glUniform1i(textureLoc_, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
}

void SimpleShaderProgram::initLocations()
{
    positionLoc_ = getAttribLocation("position");
    useObjRefLoc_ = getUniformLocation("useObjRef");
    objRefLoc_ = getUniformLocation("objRef");
    viewportSizeLoc_ = getUniformLocation("viewportSize");
    viewportOriginLoc_ = getUniformLocation("viewportOrigin");
    colorLoc_ = getUniformLocation("color");
    useColorLoc_ = getUniformLocation("useColor");
    texPosLoc_ = getAttribLocation("texPos");
    textureLoc_ = getUniformLocation("texture");
    useDirectionLoc_ = getUniformLocation("useDirection");
    directionLoc_ = getUniformLocation("direction");
    useTexColorLoc_ = getUniformLocation("useTexColor");
    texColorLoc_ = getUniformLocation("texColor");
    alphaLoc_ = getUniformLocation("alpha");
}

} // end of namespace botlib
} // end of namespace mcdane

