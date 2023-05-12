#ifndef INCLUDED_BOTLIB_WIDGET_GROUP_H
#define INCLUDED_BOTLIB_WIDGET_GROUP_H

#include <vector>
#include <memory>
#include <botlib_widget.h>

namespace mcdane {
namespace botlib {

class WidgetGroup {
public:
    WidgetGroup();

    virtual ~WidgetGroup();

    void init(unsigned int widgetCount);

    inline unsigned int widgetCount() const;

    template <typename T>
    inline T *widget(unsigned int idx);

    void setWidget(unsigned int idx, Widget *widget);

    bool process(const commonlib::InputEvent &event);

    void present();

    void shiftPos(float dx, float dy);

    inline bool visible() const;

    inline void setVisible(bool v);

    void update(float timeDelta);

protected:
#ifdef DESKTOP_APP
    bool process(const commonlib::KeyEvent &event);

    bool process(const commonlib::MouseMoveEvent &event);

    bool process(const commonlib::MouseButtonEvent &event);
#endif

    bool onPointerOver(float x, float y);

    bool onPointerDown(float x, float y);

    bool onPointerUp(float x, float y);

    int findWidget(float x, float y);

protected:
    std::vector<Widget *> widgets_;
    int hoverWidgetIdx_;
    int focusWidgetIdx_;
    bool visible_;
};

unsigned int WidgetGroup::widgetCount() const
{
    return widgets_.size();
}

template <typename T>
T *WidgetGroup::widget(unsigned int idx)
{
    return static_cast<T *>(widgets_[idx]);
}

bool WidgetGroup::visible() const
{
    return visible_;
}

void WidgetGroup::setVisible(bool v)
{
    visible_ = v;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
