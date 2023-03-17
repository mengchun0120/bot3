#ifndef INCLUDED_BOTLIB_POLYGON_H
#define INCLUDED_BOTLIB_POLYGON_H

#include <botlib_shape.h>

namespace mcdane {
namespace botlib {

class Polygon: public Shape {
public:
    Polygon() = default;

    Polygon(std::initializer_list<commonlib::Point2> positions);

    Polygon(std::initializer_list<commonlib::Point2> positions,
            const TexPosArray &texPosArray);

    Polygon(const commonlib::Point2 *positions,
            unsigned int numPositions,
            const commonlib::Point2 *texPos=nullptr);

    ~Polygon() override = default;

    void draw(SimpleShaderProgram &program,
              const commonlib::Point2 *objRef,
              const commonlib::Point2 *direction,
              const commonlib::Color *fillColor,
              const commonlib::Color *borderColor,
              const GLuint textureId,
              const commonlib::Color *texColor,
              int fillMode=GL_TRIANGLE_FAN,
              GLint fillStart=0,
              GLsizei fillVertexCount=0,
              int borderMode=GL_LINE_LOOP,
              GLint borderStart=1,
              GLsizei borderVertexCount=0) const override;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

