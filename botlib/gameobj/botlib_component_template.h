#ifndef INCLUDED_BOTLIB_COMPONENT_TEMPLATE_H
#define INCLUDED_BOTLIB_COMPONENT_TEMPLATE_H

#include <commonlib_vector.h>
#include <botlib_typedef.h>
#include <botlib_icon_template.h>
#include <botlib_component_type.h>

namespace mcdane {
namespace botlib {

class ComponentTemplate {
public:
    ComponentTemplate() = default;

    ~ComponentTemplate() = default;

    void init(const rapidjson::Value& v,
              const IconTemplateLib& iconLib);

    inline ComponentType type() const;

    inline const Rectangle* rect() const;

    inline const commonlib::Texture* texture() const;

    inline float span() const;

    inline const commonlib::Vector2& firePos() const;

private:
    void resetSpan();

private:
    ComponentType type_;
    const IconTemplate* icon_;
    float span_;
    commonlib::Vector2 firePos_;
};

ComponentType ComponentTemplate::type() const
{
    return type_;
}

const Rectangle* ComponentTemplate::rect() const
{
    return icon_->rect();
}

const commonlib::Texture* ComponentTemplate::texture() const
{
    return icon_->texture();
}

float ComponentTemplate::span() const
{
    return span_;
}

const commonlib::Vector2& ComponentTemplate::firePos() const
{
    return firePos_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

