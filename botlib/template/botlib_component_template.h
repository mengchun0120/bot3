#ifndef INCLUDED_BOTLIB_COMPONENT_TEMPLATE_H
#define INCLUDED_BOTLIB_COMPONENT_TEMPLATE_H

#include <commonlib_named_object.h>
#include <botlib_typedef.h>

namespace mcdane {
namespace botlib {

class ComponentTemplate {
public:
    ComponentTemplate() = default;

    ComponentTemplate(const commonlib::Texture* texture1,
                      const Rectangle* rect1);

    ~ComponentTemplate() = default;

    void init(const commonlib::Texture* texture1,
              const Rectangle* rect1);

    void init(const rapidjson::Value& v,
              const TextureLib& textureLib,
              const RectLib& rectLib);

    inline const commonlib::Texture* texture() const;

    inline const Rectangle* rect() const;

    inline float span() const;

private:
    void resetSpan();

private:
    const commonlib::Texture* texture_;
    const Rectangle* rect_;
    float span_;
};

const commonlib::Texture* ComponentTemplate::texture() const
{
    return texture_;
}

const Rectangle* ComponentTemplate::rect() const
{
    return rect_;
}

float ComponentTemplate::span() const
{
    return span_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

