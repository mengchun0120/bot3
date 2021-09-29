#ifndef INCLUDED_BOTLIB_SHAPE_H
#define INCLUDED_BOTLIB_SHAPE_H

#include <initializer_list>
#include <commonlib_vector.h>
#include <commonlib_vertex_array.h>
#include <botlib_simple_shader_program.h>
#include <botlib_tex_pos_array.h>

namespace mcdane {
namespace botlib {

class Shape {
public:
    Shape() = default;

    Shape(std::initializer_list<commonlib::Point2> positions);

    Shape(std::initializer_list<commonlib::Point2> positions,
          const TexPosArray& texPosArray);

    Shape(const commonlib::Point2* positions,
          unsigned int numPositions,
          const commonlib::Point2* texPos=nullptr);

    virtual ~Shape() = default;

    virtual void load(std::initializer_list<commonlib::Point2> positions);

    virtual void load(std::initializer_list<commonlib::Point2> positions,
                      const TexPosArray& texPosArray);

    virtual void load(const commonlib::Point2* positions,
                      unsigned int numPositions,
                      const commonlib::Point2* texPos=nullptr);

    virtual void draw(SimpleShaderProgram& program,
                      const commonlib::Point2* objRef,
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

