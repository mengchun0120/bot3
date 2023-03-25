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

    void process(const commonlib::InputEvent &event);

    void present();

    void shiftPos(float dx, float dy);

    inline bool visible() const;

    inline void setVisible(bool v);

protected:
#ifdef DESKTOP_APP
    void process(const commonlib::KeyEvent &event);

    void process(const commonlib::MouseMoveEvent &event);

    void process(const commonlib::MouseButtonEvent &event);
#endif

    void onPointerOver(float x, float y);

    void onPointerDown(float x, float y);

    void onPointerUp(float x, float y);

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
