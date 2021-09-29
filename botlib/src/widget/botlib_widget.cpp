#include <string>
#include <commonlib_exception.h>
#include <botlib_widget.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

Widget::Widget()
    : visible_(true)
    , acceptInput_(false)
{
}

void Widget::init(float x,
                  float y,
                  float width,
                  float height,
                  bool visible,
                  bool acceptInput,
                  bool hasTexture)
{
    if (width <= 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid width " + std::to_string(width));
    }

    if (height <= 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid height " + std::to_string(width));
    }

    visible_ = visible;
    acceptInput_ = acceptInput;

    if (hasTexture)
    {
        rect_.load(width, height, TexRectangle());
    }
    else
    {
        rect_.load(width, height);
    }

    Widget::setPos(x, y);
}

void Widget::setPos(float x,
                    float y)
{
    pos_[0] = x;
    pos_[1] = y;
}

void Widget::shiftPos(float dx, float dy)
{
    pos_[0] += dx;
    pos_[1] += dy;
}

bool Widget::containPos(float x,
                        float y) const
{
    if (!visible_)
    {
        return false;
    }

    float w = rect_.width() / 2.0f;
    float h = rect_.height() / 2.0f;

    return pos_[0] - w <= x &&
           pos_[0] + w >= x &&
           pos_[1] - h <= y &&
           pos_[1] + h >= y;
}

} // end of namespace botlib
} // end of namespace mcdane

