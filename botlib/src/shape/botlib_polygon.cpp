#include <iostream>
#include <commonlib_exception.h>
#include <commonlib_algorithm.h>
#include <botlib_polygon.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

Polygon::Polygon(std::initializer_list<commonlib::Point3> positions)
{
    load(positions);
}

Polygon::Polygon(std::initializer_list<commonlib::Point3> positions,
                 const TexPosArray& texPosArray)
{
    load(positions, texPosArray);
}

Polygon::Polygon(const Point3* positions,
                 unsigned int numPositions,
                 const Point2* texPos)
{
    load(positions, numPositions, texPos);
}

void Polygon::load(std::initializer_list<commonlib::Point3> positions)
{
    if (count(positions.begin(), positions.end()) < MIN_NUM_VERTICES)
    {
        THROW_EXCEPT(InvalidArgumentException, "positions size is less than 4");
    }

    Shape::load(positions);
}

void Polygon::load(std::initializer_list<commonlib::Point3> positions,
                   const TexPosArray& texPosArray)
{
    if (count(positions.begin(), positions.end()) < MIN_NUM_VERTICES)
    {
        THROW_EXCEPT(InvalidArgumentException, "positions size is less than 4");
    }

    Shape::load(positions, texPosArray);
}

void Polygon::load(const Point3* positions,
                   unsigned int numPositions,
                   const Point2* texPos)
{
    if (numPositions < MIN_NUM_VERTICES)
    {
        THROW_EXCEPT(InvalidArgumentException, "numPositions is less than 3");
    }

    Shape::load(positions, numPositions, texPos);
}

void Polygon::draw(SimpleShaderProgram& program,
                   const Point2* objRef,
                   const Point2* direction,
                   const Color* fillColor,
                   const Color* borderColor,
                   const GLuint textureId,
                   const Color* texColor) const
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
            glDrawArrays(GL_TRIANGLE_FAN, 0, va_.numVertices(0));
        }

        if (borderColor)
        {
            program.setColor(*borderColor);
            glDrawArrays(GL_LINE_LOOP, 1, va_.numVertices(0)-2);
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

        glDrawArrays(GL_TRIANGLE_FAN, 0, va_.numVertices(0));
    }
}

} // end of namespace botlib
} // end of namespace mcdane

