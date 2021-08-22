#ifndef INCLUDED_BOTLIB_RECTANGLE_H
#define INCLUDED_BOTLIB_RECTANGLE_H

#include <botlib_polygon.h>
#include <botlib_tex_rectangle.h>

namespace mcdane {
namespace botlib {

class Rectangle: public Polygon {
public:
    Rectangle();

    Rectangle(float width,
              float height,
              float z);

    Rectangle(float width,
              float height,
              float z,
              const TexRectangle& texRect);

    ~Rectangle() override = default;

    void load(float width,
              float height,
              float z);

    void load(float width,
              float height,
              float z,
              const TexRectangle& texRect);

    float width() const
    {
        return width_;
    }

    float height() const
    {
        return height_;
    }

private:
    float width_, height_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

