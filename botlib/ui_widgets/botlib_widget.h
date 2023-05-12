#ifndef INCLUDED_BOTLIB_WIDGET_H
#define INCLUDED_BOTLIB_WIDGET_H

#include <commonlib_opengl.h>
#include <commonlib_vector.h>
#include <commonlib_input_event.h>
#include <botlib_rectangle.h>
#include <botlib_constants.h>

namespace mcdane {
namespace botlib {

class Widget {
public:
    Widget();

    virtual ~Widget() = default;

    void init(float x,
              float y,
              bool visible=true,
              bool acceptInput=false);

#ifdef DESKTOP_APP
    inline virtual void onKey(const commonlib::KeyEvent &e);
#endif

    inline virtual void onGetFocus();

    inline virtual void onLostFocus();

    inline virtual void onPointerOut();

    inline virtual void onPointerOver(float x, float y);

    inline virtual void onPointerDown(float x, float y);

    inline virtual void onPointerUp(float x, float y);

    virtual void setPos(float x, float y);

    virtual void shiftPos(float dx, float dy);

    virtual void present() const = 0;

    inline virtual void update(float timeDelta);

    inline bool visible() const;

    inline void setVisible(bool visible);

    virtual bool containPos(float x, float y) const = 0;

    inline bool acceptInput() const;

    inline void setAcceptInput(bool accept);

    inline const commonlib::Vector2 &pos() const;

protected:
    commonlib::Vector2 pos_;
    bool visible_;
    bool acceptInput_;
};

#ifdef DESKTOP_APP
void Widget::onKey(const commonlib::KeyEvent &e)
{
}
#endif

void Widget::onGetFocus()
{
}

void Widget::onLostFocus()
{
}

void Widget::onPointerOut()
{
}

void Widget::onPointerOver(float x, float y)
{
}

void Widget::onPointerDown(float x, float y)
{
}

void Widget::onPointerUp(float x, float y)
{
}

void Widget::update(float timeDelta)
{
}

bool Widget::visible() const
{
    return visible_;
}

void Widget::setVisible(bool visible)
{
    visible_ = visible;
}

bool Widget::acceptInput() const
{
    return acceptInput_;
}

void Widget::setAcceptInput(bool accept)
{
    acceptInput_ = accept;
}

const commonlib::Vector2 &Widget::pos() const
{
    return pos_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
