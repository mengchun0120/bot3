#include <string>
#include <commonlib_exception.h>
#include <botlib_widget.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

Widget::Widget()
    : pos_({0.0f, 0.0f})
    , visible_(true)
    , acceptInput_(false)
{
}

void Widget::init(float x,
                  float y,
                  bool visible,
                  bool acceptInput)
{
    visible_ = visible;
    acceptInput_ = acceptInput;
    Widget::setPos(x, y);
}

void Widget::setPos(float x, float y)
{
    pos_[0] = x;
    pos_[1] = y;
}

void Widget::shiftPos(float dx, float dy)
{
    pos_[0] += dx;
    pos_[1] += dy;
}

} // end of namespace botlib
} // end of namespace mcdane

