#ifndef INCLUDED_BOTLIB_COMPONENT_H
#define INCLUDED_BOTLIB_COMPONENT_H

#include <ostream>
#include <commonlib_vector.h>
#include <botlib_component_template.h>
#include <commonlib_object.h>

namespace mcdane {
namespace botlib {

class Component: public commonlib::Object {
public:
    Component();

    Component(const Component& other);

    void init(const ComponentTemplate* t,
              const commonlib::Vector2& pos1,
              const commonlib::Vector2& direction1);

    inline const ComponentTemplate* getTemplate() const;

    inline float x() const;

    inline float y() const;

    inline const commonlib::Vector2& pos() const;

    inline float directionX() const;

    inline float directionY() const;

    inline const commonlib::Vector2& direction() const;

    Component& operator=(const Component& other);

    void setTemplate(const ComponentTemplate* t);

    void setPos(const commonlib::Vector2& pos1);

    void shiftPos(const commonlib::Vector2& delta);

    void setDirection(const commonlib::Vector2& direction1);

    void present() const;

    rapidjson::Value toJson(
                rapidjson::Document::AllocatorType& allocator) const override;

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

namespace std {

ostream& operator<<(ostream& os,
                    const mcdane::botlib::Component& component);

} // end of namespace std

#endif

