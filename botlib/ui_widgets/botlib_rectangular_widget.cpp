#include <commonlib_log.h>
#include <botlib_rectangular_widget.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void RectangularWidget::init(float x,
                             float y,
                             float width,
                             float height,
                             bool visible,
                             bool acceptInput,
                             bool hasTexture)
{
    Widget::init(x, y, visible, acceptInput);

    if (hasTexture)
    {
        rect_.init(width, height, TexRectangle());
    }
    else
    {
        rect_.init(width, height);
    }

    initRegion();
}

void RectangularWidget::setPos(float x, float y)
{
    Widget::setPos(x, y);
    initRegion();
}

void RectangularWidget::shiftPos(float dx, float dy)
{
    Widget::shiftPos(dx, dy);
    initRegion();
}

void RectangularWidget::initRegion()
{
    float w = rect_.width() / 2.0f;
    float h = rect_.height() / 2.0f;

    region_.init(pos_[0] - w,
                 pos_[0] + w,
                 pos_[1] - h,
                 pos_[1] + h);
}

} // end of namespace botlib
} // end of namespace mcdane

