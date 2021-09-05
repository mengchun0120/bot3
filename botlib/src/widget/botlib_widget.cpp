#include <string>
#include <commonlib_exception.h>
#include <botlib_widget.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

Widget::Widget()
    : x_(0.0f)
    , y_(0.0f)
    , visible_(true)
    , acceptInput_(false)
{
}

void Widget::init(float x,
                  float y,
                  float width,
                  float height,
                  GLuint textureId,
                  bool visible,
                  bool acceptInput)
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

    setPos(x, y);
    visible_ = visible;
    acceptInput_ = acceptInput;

    if (textureId)
    {
        rect_.load(width, height, TexRectangle());
    }
    else
    {
        rect_.load(width, height);
    }
}

void Widget::setPos(float x,
                    float y)
{
    x_ = x;
    y_ = y;
}

void Widget::shiftPos(float dx, float dy)
{
    x_ += dx;
    y_ += dy;
}

bool Widget::containPos(float x,
                        float y) const
{
    if (!visible_)
    {
        return false;
    }

    return x_ <= x &&
           x <= x_ + rect_.width() &&
           y_ <= y &&
           y <= y_ + rect_.height();
}

} // end of namespace botlib
} // end of namespace mcdane

