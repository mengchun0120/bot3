#include <commonlib_exception.h>
#include <commonlib_math_utils.h>
#include <botlib_tex_rectangle.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void validateParamForTexRect(float width,
                             float height,
                             float centerX,
                             float centerY)
{
    if (width < 0.0f || width > 1.0f)
    {
        THROW_EXCEPT(InvalidArgumentException, "width out of bound");
    }

    if (height < 0.0f || height > 1.0f)
    {
        THROW_EXCEPT(InvalidArgumentException, "height out of bound");
    }

    if (centerX < 0.0f || centerX > 1.0f)
    {
        THROW_EXCEPT(InvalidArgumentException, "centerX out of bound");
    }

    if (centerY < 0.0f || centerY > 1.0f)
    {
        THROW_EXCEPT(InvalidArgumentException, "centerY out of bound");
    }
}

TexRectangle::TexRectangle(float width,
                           float height,
                           float centerX,
                           float centerY)
{
    validateParamForTexRect(width, height, centerX, centerY);

    float w = width/2.0f, h = height/2.0f;
    float left = clamp(centerX-w, 0.0f, 1.0f);
    float right = clamp(centerX+w, 0.0f, 1.0f);
    float bottom = clamp(centerY-h, 0.0f, 1.0f);
    float top = clamp(centerY+h, 0.0f, 1.0f);

    load({
        Point2{centerX, centerY},
        Point2{right, top},
        Point2{left, top},
        Point2{left, bottom},
        Point2{right, bottom},
        Point2{right, top}
    });
}

} // end of namespace botlib
} // end of namespace mcdane

