#ifndef INCLUDED_BOTLIB_RECTANGLE_H
#define INCLUDED_BOTLIB_RECTANGLE_H

#include <ostream>
#include <botlib_polygon.h>
#include <botlib_tex_rectangle.h>

namespace mcdane {
namespace botlib {

class Rectangle: public Polygon {
public:
    Rectangle() = default;

    Rectangle(float width,
              float height);

    Rectangle(float width,
              float height,
              const TexRectangle& texRect);

    ~Rectangle() override = default;

    void load(float width,
              float height);

    void load(float width,
              float height,
              const TexRectangle& texRect);

    float width() const
    {
        return width_;
    }

    float height() const
    {
        return height_;
    }

    rapidjson::Value toJson(
                rapidjson::Document::AllocatorType& allocator) const override;

private:
    float width_, height_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

