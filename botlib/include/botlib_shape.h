#ifndef INCLUDED_BOTLIB_SHAPE_H
#define INCLUDED_BOTLIB_SHAPE_H

#include <initializer_list>
#include <commonlib_vector.h>
#include <commonlib_vertex_array.h>

namespace mcdane {
namespace botlib {

class Shape {
public:
    Shape() = default;

    Shape(commonlib::Point3* positions,
          unsigned int numPositions,
          commonlib::Point2* texPos=nullptr);

    virtual ~Shape() = default;

    void load(commonlib::Point3* positions,
              unsigned int numPositions,
              commonlib::Point2* texPos=nullptr);

    virtual void draw(const commonlib::Point3* pos,
                      const commonlib::Point2* direction,
                      const commonlib::Color* fillColor,
                      const commonlib::Color* borderColor,
                      const GLuint textureId,
                      const commonlib::Color* texColor) const = 0;

    const commonlib::VertexArray &vertexArray() const
    {
        return va_;
    }

protected:
    commonlib::VertexArray va_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

