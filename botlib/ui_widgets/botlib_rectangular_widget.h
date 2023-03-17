#ifndef INCLUDED_BOTLIB_RECTANGULAR_WIDGET_H
#define INCLUDED_BOTLIB_RECTANGULAR_WIDGET_H

#include <commonlib_region.h>
#include <botlib_widget.h>

namespace mcdane {
namespace botlib {

class RectangularWidget: public Widget {
public:
    RectangularWidget() = default;

    ~RectangularWidget() override = default;

    void init(float x,
              float y,
              float width,
              float height,
              bool visible=true,
              bool acceptInput=false,
              bool hasTexture=false);

    inline float width() const;

    inline float height() const;

    inline const Rectangle &rect() const;

    void setPos(float x, float y) override;

    void shiftPos(float dx, float dy) override;

    inline bool containPos(float x, float y) const override;

private:
    void initRegion();

protected:
    Rectangle rect_;
    commonlib::Region<float> region_;
};

float RectangularWidget::width() const
{
    return rect_.width();
}

float RectangularWidget::height() const
{
    return rect_.height();
}

const Rectangle &RectangularWidget::rect() const
{
    return rect_;
}

bool RectangularWidget::containPos(float x, float y) const
{
    return visible_ && region_.contains(x, y);
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
