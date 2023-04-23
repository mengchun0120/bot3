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

WidgetGroup::~WidgetGroup()
{
    for (auto widget: widgets_)
    {
        delete widget;
    }
}

void WidgetGroup::init(unsigned int widgetCount)
{
    widgets_.resize(widgetCount, nullptr);
}

void WidgetGroup::setWidget(unsigned int idx, Widget *widget)
{
    widgets_[idx] = widget;
}

#ifdef DESKTOP_APP
bool WidgetGroup::process(const InputEvent &event)
{

    switch (event.type())
    {
        case EventType::KEY:
            return process(event.keyEvent());
        case EventType::MOUSE_MOVE:
            return process(event.mouseMoveEvent());
        case EventType::MOUSE_BUTTON:
            return process(event.mouseButtonEvent());
        default:
            LOG_WARN << "Invalid event type " << static_cast<int>(event.type())
                     << LOG_END;
            break;
    }

    return false;
}
#elif __ANDROID__
bool WidgetGroup::process(const InputEvent &event)
{
    switch (event.type_)
    {
        case InputEvent::POINTER_DOWN:
            return onPointerDown(event.x_, event.y_);
        case InputEvent::POINTER_MOVE:
            return onPointerOver(event.x_, event.y_);
        case InputEvent::POINTER_UP:
            return onPointerUp(event.x_, event.y_);
        default:
            LOG_WARN << "Invalid type " << static_cast<int>(event.type_)
                     << LOG_END;
            break;
    }

    return false;
}
#endif

void WidgetGroup::present()
{
    if (!visible_)
    {
        return;
    }

    for (auto widget : widgets_)
    {
        widget->present();
    }
}

void WidgetGroup::shiftPos(float dx, float dy)
{
    for (auto widget : widgets_)
    {
        widget->shiftPos(dx, dy);
    }
}

#ifdef DESKTOP_APP
bool WidgetGroup::process(const KeyEvent &event)
{
    if (focusWidgetIdx_ < 0)
    {
        return false;
    }

    widgets_[focusWidgetIdx_]->onKey(event);
    return true;
}

bool WidgetGroup::process(const MouseMoveEvent &event)
{
    return onPointerOver(event.x_, event.y_);
}

bool WidgetGroup::process(const MouseButtonEvent &event)
{
    if (event.button_ != GLFW_MOUSE_BUTTON_LEFT)
    {
        return false;
    }

    if (event.action_ == GLFW_PRESS)
    {
        return onPointerDown(event.x_, event.y_);
    }
    else if (event.action_ == GLFW_RELEASE)
    {
        return onPointerUp(event.x_, event.y_);
    }

    return true;
}
#endif

bool WidgetGroup::onPointerOver(float x, float y)
{
    int idx = findWidget(x, y);

    if (idx != hoverWidgetIdx_ && hoverWidgetIdx_ != -1)
    {
        widgets_[hoverWidgetIdx_]->onPointerOut();
        return true;
    }

    if (idx == -1)
    {
        hoverWidgetIdx_ = -1;
        return false;
    }

    hoverWidgetIdx_ = idx;
    widgets_[hoverWidgetIdx_]->onPointerOver(x, y);

    return true;
}

bool WidgetGroup::onPointerDown(float x, float y)
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

    if (idx < 0)
    {
        return false;
    }

    widgets_[idx]->onPointerDown(x, y);

    return true;
}

bool WidgetGroup::onPointerUp(float x, float y)
{
    int idx = findWidget(x, y);
    if (idx < 0)
    {
        return false;
    }

    widgets_[idx]->onPointerUp(x, y);

    return true;
}

int WidgetGroup::findWidget(float x, float y)
{
    for (unsigned int i = 0; i < widgets_.size(); ++i)
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
