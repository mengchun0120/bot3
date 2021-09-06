#ifndef INCLUDED_BOTLIB_WIDGET_H
#define INCLUDED_BOTLIB_WIDGET_H

#include <commonlib_opengl.h>
#include <commonlib_input_event.h>
#include <botlib_rectangle.h>
#include <botlib_text_system.h>
#include <botlib_constants.h>

namespace mcdane {
namespace botlib {

class Widget {
public:
    Widget();

    virtual ~Widget() = default;

    void init(float x,
              float y,
              float z,
              float width,
              float height,
              bool visible=true,
              bool acceptInput=false,
              bool hasTexture=false);

#ifdef DESKTOP_APP
    virtual inline void process(const commonlib::KeyEvent& e);

    virtual inline void process(const commonlib::MouseMoveEvent& e);

    virtual inline void process(const commonlib::MouseButtonEvent& e);

    virtual inline void onLostFocus();

    virtual inline void onMouseOut();
#endif

    virtual void setPos(float x,
                        float y
                        float z);

    virtual void shiftPos(float dx,
                          float dy);

    virtual void present(SimpleShaderProgram& shader,
                         TextSystem& textSys) const = 0;

    inline bool visible() const;

    inline void setVisible(bool visible);

    bool containPos(float x,
                    float y) const;

    inline bool acceptInput() const;

    inline void setAcceptInput(bool accept);

    inline float width() const;

    inline float height() const;

    inline commonlib::Vecotr2& pos() const;

    inline float z() const;

    inline const Rectangle& rect() const;

protected:
    commonlib::Vector2 pos_;
    float z_;
    Rectangle rect_;
    bool visible_;
    bool acceptInput_;
};

#ifdef DESKTOP_APP
void Widget::process(const commonlib::KeyEvent& e)
{
}

void Widget::process(const commonlib::MouseMoveEvent& e)
{
}

void Widget::process(const commonlib::MouseButtonEvent& e)
{
}

void Widget::onLostFocus()
{
}

void Widget::onMouseOut()
{
}
#endif

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

const commonlib::Vector& Widget::pos() const
{
    return pos_;
}

float Widget::z() const
{
    return z_;
}

const Rectangle& Widget::rect() const
{
    return rect_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
