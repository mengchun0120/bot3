#ifndef INCLUDED_BOTLIB_SIMPLE_SHADER_PROGRAM_H
#define INCLUDED_BOTLIB_SIMPLE_SHADER_PROGRAM_H

#include <commonlib_vertex_array.h>
#include <commonlib_shader_program.h>

namespace mcdane {
namespace botlib {

class SimpleShaderProgram: public commonlib::ShaderProgram {
public:
    SimpleShaderProgram() = default;

    ~SimpleShaderProgram() override = default;

    void init(const std::string& vertexShaderFile,
              const std::string& fragShaderFile);

    void setUseObjRef(bool enabled)
    {
        glUniform1i(useObjRefLoc_, enabled ? 1 : 0);
    }

    void setObjRef(const float* objRef)
    {
        glUniform2fv(objRefLoc_, 1, objRef);
    }

    void setViewportSize(const float* viewportSize)
    {
        glUniform2fv(viewportSizeLoc_, 1, viewportSize);
    }

    void setViewportOrigin(const float* viewportOrigin)
    {
        glUniform2fv(viewportOriginLoc_, 1, viewportOrigin);
    }

    void setPositionTexPos(const commonlib::VertexArray& va);

    void setColor(const float* color)
    {
        glUniform4fv(colorLoc_, 1, color);
    }

    void setUseColor(bool use)
    {
        glUniform1i(useColorLoc_, use ? 1 : 0);
    }

    void setTexture(GLuint textureId);

    void setUseDirection(bool use)
    {
        glUniform1i(useDirectionLoc_, use ? 1 : 0);
    }

    void setDirection(const float* direction)
    {
        glUniform2fv(directionLoc_, 1, direction);
    }

    void setUseTexColor(bool use)
    {
        glUniform1i(useTexColorLoc_, use ? 1 : 0);
    }

    void setTexColor(const float* color)
    {
        glUniform4fv(texColorLoc_, 1, color);
    }

private:
    GLint positionLoc_;
    GLint useObjRefLoc_;
    GLint objRefLoc_;
    GLint viewportSizeLoc_;
    GLint viewportOriginLoc_;
    GLint colorLoc_;
    GLint useColorLoc_;
    GLint texPosLoc_;
    GLint textureLoc_;
    GLint useDirectionLoc_;
    GLint directionLoc_;
    GLint useTexColorLoc_;
    GLint texColorLoc_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

