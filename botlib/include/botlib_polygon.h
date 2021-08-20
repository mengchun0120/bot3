#ifndef INCLUDED_BOTLIB_POLYGON_H
#define INCLUDED_BOTLIB_POLYGON_H

#include <botlib_shape.h>

namespace mcdane {
namespace botlib {

class Polygon: public Shape {
public:
    Polygon() = default;

    Polygon(commonlib::Point3* positions,
            unsigned int numPositions,
            commonlib::Point2* texPos=nullptr);

    ~Polygon() override = default;

    void load(commonlib::Point3* positions,
              unsigned int numPositions,
              commonlib::Point2* texPos=nullptr) override;

    void draw(const commonlib::Point2* objRef,
              const commonlib::Point2* direction,
              const commonlib::Color* fillColor,
              const commonlib::Color* borderColor,
              const GLuint textureId,
              const commonlib::Color* texColor) const override;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

