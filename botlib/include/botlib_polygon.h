#ifndef INCLUDED_BOTLIB_POLYGON_H
#define INCLUDED_BOTLIB_POLYGON_H

#include <botlib_shape.h>
#include <botlib_tex_pos_array.h>

namespace mcdane {
namespace botlib {

class Polygon: public Shape {
public:
    static constexpr unsigned int MIN_NUM_VERTICES = 4;

    Polygon() = default;

    Polygon(std::initializer_list<commonlib::Point2> positions);

    Polygon(std::initializer_list<commonlib::Point2> positions,
            const TexPosArray& texPosArray);

    Polygon(const commonlib::Point2* positions,
            unsigned int numPositions,
            const commonlib::Point2* texPos=nullptr);

    ~Polygon() override = default;

    void load(std::initializer_list<commonlib::Point2> positions) override;

    void load(std::initializer_list<commonlib::Point2> positions,
              const TexPosArray& texPosArray) override;

    void load(const commonlib::Point2* positions,
              unsigned int numPositions,
              const commonlib::Point2* texPos=nullptr) override;

    void draw(SimpleShaderProgram& program,
              const commonlib::Point2* objRef,
              const commonlib::Point2* direction,
              const commonlib::Color* fillColor,
              const commonlib::Color* borderColor,
              const GLuint textureId,
              const commonlib::Color* texColor) const override;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

