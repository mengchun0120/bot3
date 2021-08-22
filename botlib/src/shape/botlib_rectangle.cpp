#include <commonlib_exception.h>
#include <botlib_rectangle.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void validateParamForRect(float width,
                          float height)
{
    if (width < 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException, "width is negative");
    }

    if (height < 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException, "height is negative");
    }
}

Rectangle::Rectangle(float width,
                     float height,
                     float z)
{
    load(width, height, z);
}

Rectangle::Rectangle(float width,
                     float height,
                     float z,
                     const TexRectangle& texRect)
{
    load(width, height, z, texRect);
}

void Rectangle::load(float width,
                     float height,
                     float z)
{
    validateParamForRect(width, height);

    float w = width/2.0f;
    float h = height/2.0f;

    Polygon::load({
        Point3{0.0f, 0.0f, z},
        Point3{w, h, z},
        Point3{-w, h, z},
        Point3{-w, -h, z},
        Point3{w, -h, z},
        Point3{w, h, z}
    });
}

void Rectangle::load(float width,
                     float height,
                     float z,
                     const TexRectangle& texRect)
{
    validateParamForRect(width, height);

    float w = width/2.0f;
    float h = height/2.0f;

    std::vector<Point3> positions({
        Point3{0.0f, 0.0f, z},
        Point3{w, h, z},
        Point3{-w, h, z},
        Point3{-w, -h, z},
        Point3{w, -h, z},
        Point3{w, h, z}
    });

    Polygon::load(positions.data(), positions.size(), texRect.texPos());
}

} // end of namespace botlib
} // end of namespace mcdane

