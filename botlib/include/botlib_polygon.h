#ifndef INCLUDED_BOTLIB_POLYGON_H
#define INCLUDED_BOTLIB_POLYGON_H

#include <botlib_shape.h>

namespace mcdane {
namespace botlib {

class Polygon: public Shape {
public:
    Polygon() = default;

    Polygon(std::initializer_list<commonlib::Point3> positions);

    Polygon(std::initializer_list<commonlib::Point3> positions,
            std::initializer_list<commonlib::Point2> texPos);

    Polygon(commonlib::Point3* positions,
            unsigned int numPositions,
            commonlib::Point2* texPos=nullptr);

    ~Polygon() override = default;

    void load(std::initializer_list<commonlib::Point3> positions) override;

    void load(std::initializer_list<commonlib::Point3> positions,
              std::initializer_list<commonlib::Point2> texPos) override;

    void load(commonlib::Point3* positions,
              unsigned int numPositions,
              commonlib::Point2* texPos=nullptr) override;

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

