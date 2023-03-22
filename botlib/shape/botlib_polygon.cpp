#include <commonlib_exception.h>
#include <commonlib_algorithm.h>
#include <botlib_simple_shader_program.h>
#include <botlib_polygon.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

Polygon::Polygon(std::initializer_list<commonlib::Point2> positions)
{
    init(positions);
}

Polygon::Polygon(std::initializer_list<commonlib::Point2> positions,
                 const TexPosArray &texPosArray)
{
    init(positions, texPosArray);
}

Polygon::Polygon(const Point2 *positions,
                 unsigned int numPositions,
                 const Point2 *texPos)
{
    init(positions, numPositions, texPos);
}

void Polygon::draw(SimpleShaderProgram &program,
                   const Point2 *objRef,
                   const Point2 *direction,
                   const Color *fillColor,
                   const Color *borderColor,
                   const GLuint textureId,
                   const Color *texColor,
                   int fillMode,
                   GLint fillStart,
                   GLsizei fillVertexCount,
                   int borderMode,
                   GLint borderStart,
                   GLsizei borderVertexCount) const
{
    if (objRef)
    {
        program.setUseObjRef(true);
        program.setObjRef(*objRef);
    }
    else
    {
        program.setUseObjRef(false);
    }

    program.setPositionTexPos(va_);
    program.setUseColor(textureId == 0);

    if (direction)
    {
        program.setUseDirection(true);
        program.setDirection(*direction);
    }
    else
    {
        program.setUseDirection(false);
    }

    if (textureId == 0)
    {
        if (fillColor)
        {
            program.setColor(*fillColor);
            GLsizei count = fillVertexCount == 0 ?
                                va_.numVertices(0) : fillVertexCount;
            glDrawArrays(fillMode, fillStart, count);
        }

        if (borderColor)
        {
            program.setColor(*borderColor);
            GLsizei count = borderVertexCount == 0?
                                va_.numVertices(0)-2 : borderVertexCount;
            glDrawArrays(borderMode, borderStart, count);
        }
    }
    else
    {
        program.setTexture(textureId);

        if(texColor)
        {
            program.setUseTexColor(true);
            program.setTexColor(*texColor);
        }
        else
        {
            program.setUseTexColor(false);
        }

        GLsizei count = fillVertexCount == 0 ?
                            va_.numVertices(0) : fillVertexCount;
        glDrawArrays(fillMode, fillStart, count);
    }
}

} // end of namespace botlib
} // end of namespace mcdane

