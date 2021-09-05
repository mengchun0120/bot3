#include <commonlib_exception.h>
#include <commonlib_log.h>
#include <botlib_widget_group.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

WidgetGroup::WidgetGroup()
    : hoverWidgetIdx_(-1)
    , focusWidgetIdx_(-1)
    , visible_(true)
{}

void WidgetGroup::init(unsigned int widgetCount)
{
    if (widgetCount == 0)
    {
        LOG_WARN << "widgetCount = 0" << LOG_END;
        return;
    }

    widgets_.resize(widgetCount);
}

std::shared_ptr<Widget> WidgetGroup::getWidget(unsigned int idx)
{
    if (idx >= widgets_.size())
    {
         THROW_EXCEPT(InvalidArgumentException,
                     "Invalid idx" + std::to_string(idx));
    }

    return widgets_[idx];
}

void WidgetGroup::setWidget(unsigned int idx,
                            Widget* widget)
{
    if (idx >= widgets_.size())
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid idx" + std::to_string(idx));
    }

    if (!widget)
    {
        THROW_EXCEPT(InvalidArgumentException, "widget is null");
    }

    widgets_[idx].reset(widget);
}

void WidgetGroup::process(const commonlib::InputEvent& event)
{
#ifdef DESKTOP_APP
    switch (event.type())
    {
        case InputEvent::ET_KEY:
        {
            process(event.keyEvent());
            break;
        }
        case InputEvent::ET_MOUSE_MOVE:
        {
            process(event.mouseMoveEvent());
            break;
        }
        case InputEvent::ET_MOUSE_BUTTON:
        {
            process(event.mouseButtonEvent());
            break;
        }
        default:
        {
            THROW_EXCEPT(InvalidArgumentException, "Invalid event type ");
        }
    }
#endif
}

void WidgetGroup::present()
{
    if (!visible_)
    {
        return;
    }

    for (auto &widget : widgets_)
    {
        widget->present();
    }
}

void WidgetGroup::shiftPos(float dx,
                           float dy)
{
    for (auto &widget : widgets_)
    {
        widget->shiftPos(dx, dy);
    }
}

#ifdef DESKTOP_APP
void WidgetGroup::process(const KeyEvent& event)
{
    if (focusWidgetIdx_ >= 0)
    {
        widgets_[focusWidgetIdx_]->process(event);
    }
}

void WidgetGroup::process(const MouseMoveEvent& event)
{
    int idx = findWidget(event.x_, event.y_);

    if (idx != hoverWidgetIdx_ && hoverWidgetIdx_ != -1)
    {
        widgets_[hoverWidgetIdx_]->onMouseOut();
    }

    if (idx == -1)
    {
        hoverWidgetIdx_ = -1;
        return;
    }

    hoverWidgetIdx_ = idx;

    widgets_[hoverWidgetIdx_]->process(event);
}

void WidgetGroup::process(const MouseButtonEvent& event)
{
    int idx = findWidget(event.x_, event.y_);
    bool handle = event.button_ == GLFW_MOUSE_BUTTON_LEFT &&
                  event.action_ == GLFW_PRESS;

    if (handle)
    {
        if (idx != focusWidgetIdx_)
        {
            if (focusWidgetIdx_ != -1)
            {
                widgets_[focusWidgetIdx_]->onLostFocus();
            }

            focusWidgetIdx_ = idx;
        }
    }

    if (idx >= 0)
    {
        widgets_[idx]->process(event);
    }
}
#endif

int WidgetGroup::findWidget(float x,
                            float y)
{
    int i, count = static_cast<int>(widgetCount());

    for (i = 0; i < count; ++i)
    {
        bool found = widgets_[i]->visible() &&
                     widgets_[i]->acceptInput() &&
                     widgets_[i]->containPos(x, y);
        if (found)
        {
            return i;
        }
    }

    return -1;
}

} // end of namespace botlib
} // end of namespace mcdane

