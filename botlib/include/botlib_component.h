#ifndef INCLUDED_BOTLIB_COMPONENT_H
#define INCLUDED_BOTLIB_COMPONENT_H

#include <commonlib_vector.h>
#include <botlib_component_template.h>

namespace mcdane {
namespace botlib {

class Component {
public:
    Component();

    Component(const Component& other);

    void init(const ComponentTemplate* t,
              float x,
              float y,
              float directionX,
              float directionY);

    void init(const ComponentTemplate* t,
              const commonlib::Vector2& pos,
              const commonlib::Vector2& direction);

    inline const ComponentTemplate* getTemplate() const;

    inline float x() const;

    inline float y() const;

    inline const commonlib::Vector2& pos() const;

    inline float directionX() const;

    inline float directionY() const;

    inline const commonlib::Vector2& direction() const;

    Component& operator=(const Component& other);

    void setTemplate(const ComponentTemplate* t);

    void setPos(float x,
                float y);

    void setPos(const commonlib::Vector2& p);

    void shiftPos(float deltaX,
                  float deltaY);

    void setDirection(float directionX,
                      float directionY);

    void setDirection(const commonlib::Vector2& d);

    void present() const;

private:
    const ComponentTemplate* t_;
    commonlib::Vector2 pos_;
    commonlib::Vector2 direction_;
};

const ComponentTemplate* Component::getTemplate() const
{
    return t_;
}

float Component::x() const
{
    return pos_[0];
}

float Component::y() const
{
    return pos_[1];
}

const commonlib::Vector2& Component::pos() const
{
    return pos_;
}

float Component::directionX() const
{
    return direction_[0];
}

float Component::directionY() const
{
    return direction_[1];
}

const commonlib::Vector2& Component::direction() const
{
    return direction_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

