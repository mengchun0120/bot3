#ifndef INCLUDED_BOTLIB_SHAPE_H
#define INCLUDED_BOTLIB_SHAPE_H

#include <initializer_list>
#include <rapidjson/document.h>
#include <commonlib_vector.h>
#include <commonlib_vertex_array.h>
#include <commonlib_opengl.h>

namespace mcdane {
namespace commonlib {

class Color;

}

namespace botlib {

class SimpleShaderProgram;
class TexPosArray;

class Shape {
public:
    Shape() = default;

    Shape(std::initializer_list<commonlib::Point2> positions);

    Shape(std::initializer_list<commonlib::Point2> positions,
          const TexPosArray &texPosArray);

    Shape(const commonlib::Point2 *positions,
          unsigned int numPositions,
          const commonlib::Point2 *texPos=nullptr);

    explicit Shape(const std::vector<commonlib::Point2> &positions);

    Shape(const std::vector<commonlib::Point2> &positions,
          const std::vector<commonlib::Point2> &texPos);

    virtual ~Shape() = default;

    void load(std::initializer_list<commonlib::Point2> positions);

    void load(std::initializer_list<commonlib::Point2> positions,
              const TexPosArray &texPosArray);

    void load(const commonlib::Point2 *positions,
              unsigned int numPositions,
              const commonlib::Point2 *texPos=nullptr);

    void load(const std::vector<commonlib::Point2> &positions);

    void load(const std::vector<commonlib::Point2> &positions,
              const std::vector<commonlib::Point2> &texPos);

    virtual void draw(SimpleShaderProgram &program,
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
                      GLsizei borderVertexCount=0) const = 0;

    inline const commonlib::VertexArray &vertexArray() const;

protected:
    commonlib::VertexArray va_;
};

const commonlib::VertexArray &Shape::vertexArray() const
{
    return va_;
}

} // end of namespace botlib

namespace commonlib {

void parse(botlib::Shape &shape, const rapidjson::Value &v);

}
} // end of namespace mcdane

#endif

