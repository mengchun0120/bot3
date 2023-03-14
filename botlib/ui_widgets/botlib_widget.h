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
              float width,
              float height,
              bool visible=true,
              bool acceptInput=false,
              bool hasTexture=false);

#ifdef DESKTOP_APP
    virtual inline void onKey(const commonlib::KeyEvent &e);
#endif

    virtual inline void onLostFocus();

    virtual inline void onPointerOut();

    virtual inline void onPointerOver();

    virtual inline void onPointerDown();

//    virtual inline void onPointerUp();

    virtual void setPos(float x,
                        float y);

    virtual void shiftPos(float dx,
                          float dy);

    virtual void present() const = 0;

    inline bool visible() const;

    inline void setVisible(bool visible);

    bool containPos(float x,
                    float y) const;

    inline bool acceptInput() const;

    inline void setAcceptInput(bool accept);

    inline float width() const;

    inline float height() const;

    inline const commonlib::Vector2& pos() const;

    inline const Rectangle& rect() const;

protected:
    commonlib::Vector2 pos_;
    Rectangle rect_;
    bool visible_;
    bool acceptInput_;
};

#ifdef DESKTOP_APP
void Widget::onKey(const commonlib::KeyEvent &e)
{
}
#endif

void Widget::onLostFocus()
{
}

void Widget::onPointerOut()
{
}

void Widget::onPointerOver()
{
}

void Widget::onPointerDown()
{
}
/*
void Widget::onPointerUp()
{
}
*/
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

float Widget::width() const
{
    return rect_.width();
}

float Widget::height() const
{
    return rect_.height();
}

const commonlib::Vector2& Widget::pos() const
{
    return pos_;
}

const Rectangle& Widget::rect() const
{
    return rect_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
