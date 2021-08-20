#include <commonlib_exception.h>
#include <botlib_polygon.h>
#include <botlib_bot_app.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

Polygon::Polygon(Point3* positions,
                 unsigned int numPositions,
                 Point2* texPos=nullptr)
{
    load(positions, numPositions, texPos);
}

void Polygon::load(Point3* positions,
                   unsigned int numPositions,
                   Point2* texPos=nullptr)
{
    if (numPositions < 4)
    {
        THROW_EXCEPT(InvalidArgumentException, "numPositions is less than 3");
    }

    Shape::load(positions, numPositions, texPos);
}

void Polygon::draw(const Point2* objRef,
                   const Point2* direction,
                   const Color* fillColor,
                   const Color* borderColor,
                   const GLuint textureId,
                   const Color* texColor) const
{
    SimpleShaderProgram program = BotApp::getInstance().simpleShaderProgram();

    if (objRef)
    {
        program.setUseObjRef(true);
        program.setObjRef(objRef);
    }
    else
    {
        program.setUseObjRef(false);
    }

    program.setPositionTexPos(vertexArray());
    program.setUseColor(textureId == 0);

    if (direction)
    {
        program.setUseDirection(true);
        program.setDirection(direction);
    }
    else
    {
        program.setUseDirection(false);
    }

    if (textureId == 0)
    {
        if (fillColor)
        {
            program.setColor(fillColor->getColor());
            glDrawArrays(GL_TRIANGLE_FAN, 0, vertexArray.numVertices());
        }

        if (borderColor)
        {
            program.setColor(borderColor->getColor());
            glDrawArrays(GL_LINE_LOOP, 1, vertexArray.numVertices()-2);
        }
    }
    else
    {
        program.setTexture(textureId);

        if(texColor)
        {
            program.setUseTexColor(true);
            program.setTexColor(texColor->getColor());
        }
        else
        {
            program.setUseTexColor(false);
        }

        glDrawArrays(GL_TRIANGLE_FAN, 0, m_vertexArray.numVertices());
    }
}

} // end of namespace botlib
} // end of namespace mcdane

