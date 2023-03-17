#ifndef INCLUDED_BOTLIB_COMPONENT_H
#define INCLUDED_BOTLIB_COMPONENT_H

#include <commonlib_vector.h>
#include <commonlib_object.h>
#include <botlib_typedef.h>
#include <botlib_component_type.h>

namespace mcdane {
namespace botlib {

class ComponentTemplate;

class Component {
public:
    Component();

    Component(const rapidjson::Value &v,
              const ComponentTemplateLib &componentTemplateLib);

    Component(const Component &other);

    void init(const rapidjson::Value &v,
              const ComponentTemplateLib &componentTemplateLib);

    inline const ComponentTemplate *getTemplate() const;

    inline float x() const;

    inline float y() const;

    inline const commonlib::Vector2 &pos() const;

    inline float directionX() const;

    inline float directionY() const;

    inline const commonlib::Vector2 &direction() const;

    inline const commonlib::Vector2 &firePos() const;

    Component &operator=(const Component& other);

    void setTemplate(const ComponentTemplate *t);

    void setPos(const commonlib::Vector2 &p);

    void shiftPos(const commonlib::Vector2 &delta);

    void setDirection(const commonlib::Vector2 &direction1);

    void present() const;

private:
    void resetFirePos();

private:
    const ComponentTemplate *t_;
    commonlib::Vector2 pos_;
    commonlib::Vector2 direction_;
    commonlib::Vector2 firePos_;
};

const ComponentTemplate *Component::getTemplate() const
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

const commonlib::Vector2 &Component::pos() const
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

const commonlib::Vector2 &Component::direction() const
{
    return direction_;
}

const commonlib::Vector2 &Component::firePos() const
{
    return firePos_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

