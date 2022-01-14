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
                     float height)
{
    load(width, height);
}

Rectangle::Rectangle(float width,
                     float height,
                     const TexRectangle& texRect)
{
    load(width, height, texRect);
}

void Rectangle::load(float width,
                     float height)
{
    validateParamForRect(width, height);

    width_ = width;
    height_ = height;

    float w = width/2.0f;
    float h = height/2.0f;

    Polygon::load({
        Point2{0.0f, 0.0f},
        Point2{w, h},
        Point2{-w, h},
        Point2{-w, -h},
        Point2{w, -h},
        Point2{w, h}
    });
}

void Rectangle::load(float width,
                     float height,
                     const TexRectangle& texRect)
{
    validateParamForRect(width, height);

    width_ = width;
    height_ = height;

    float w = width/2.0f;
    float h = height/2.0f;

    std::vector<Point2> positions({
        Point2{0.0f, 0.0f},
        Point2{w, h},
        Point2{-w, h},
        Point2{-w, -h},
        Point2{w, -h},
        Point2{w, h}
    });

    Polygon::load(positions.data(), positions.size(), texRect.texPos());
}

} // end of namespace botlib
} // end of namespace mcdane

namespace std {

ostream& operator<<(ostream& os,
                    const mcdane::botlib::Rectangle& rect)
{
    os << "Rectangle(" << &rect
       << ", width=" << rect.width()
       << ", height=" << rect.height()
       << ")";

    return os;
}

} // end of namespace std


