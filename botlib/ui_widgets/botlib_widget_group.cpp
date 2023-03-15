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

#ifdef DESKTOP_APP
void WidgetGroup::process(const InputEvent &event)
{

    switch (event.type())
    {
        case EventType::KEY:
            process(event.keyEvent());
            break;
        case EventType::MOUSE_MOVE:
            process(event.mouseMoveEvent());
            break;
        case EventType::MOUSE_BUTTON:
            process(event.mouseButtonEvent());
            break;
        default:
            LOG_WARN << "Invalid event type " << static_cast<int>(event.type())
                     << LOG_END;
            break;
    }
}
#elif __ANDROID__
void WidgetGroup::process(const InputEvent &event)
{
    switch (event.type_)
    {
        case InputEvent::POINTER_DOWN:
            onPointerDown(event.x_, event.y_);
            break;
        case InputEvent::POINTER_MOVE:
            onPointerOver(event.x_, event.y_);
            break;
        default:
            LOG_WARN << "Invalid type " << static_cast<int>(event.type_)
                     << LOG_END;
            break;
    }
}
#endif

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
void WidgetGroup::process(const KeyEvent &event)
{
    if (focusWidgetIdx_ >= 0)
    {
        widgets_[focusWidgetIdx_]->onKey(event);
    }
}

void WidgetGroup::process(const MouseMoveEvent &event)
{
    onPointerOver(event.x_, event.y_);
}

void WidgetGroup::process(const MouseButtonEvent &event)
{
    if (event.button_ != GLFW_MOUSE_BUTTON_LEFT)
    {
        return;
    }

    if (event.action_ == GLFW_PRESS)
    {
        onPointerDown(event.x_, event.y_);
    }
}
#endif

void WidgetGroup::onPointerOver(float x, float y)
{
    int idx = findWidget(x, y);

    if (idx != hoverWidgetIdx_ && hoverWidgetIdx_ != -1)
    {
        widgets_[hoverWidgetIdx_]->onPointerOut();
    }

    if (idx == -1)
    {
        hoverWidgetIdx_ = -1;
        return;
    }

    hoverWidgetIdx_ = idx;

    widgets_[hoverWidgetIdx_]->onPointerOver();
}

void WidgetGroup::onPointerDown(float x, float y)
{
    int idx = findWidget(x, y);

    if (idx != focusWidgetIdx_)
    {
        if (focusWidgetIdx_ != -1)
        {
            widgets_[focusWidgetIdx_]->onLostFocus();
        }

        focusWidgetIdx_ = idx;
    }

    if (idx >= 0)
    {
        widgets_[idx]->onPointerDown();
    }
}

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
