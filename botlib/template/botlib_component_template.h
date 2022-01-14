#ifndef INCLUDED_BOTLIB_COMPONENT_TEMPLATE_H
#define INCLUDED_BOTLIB_COMPONENT_TEMPLATE_H

#include <ostream>
#include <commonlib_texture.h>
#include <botlib_rectangle.h>

namespace mcdane {
namespace botlib {

class ComponentTemplate {
public:
    ComponentTemplate() = default;

    ComponentTemplate(const commonlib::Texture* texture,
                      const Rectangle* rect);

    ~ComponentTemplate() = default;

    void init(const commonlib::Texture* texture,
              const Rectangle* rect);

    inline const commonlib::Texture* texture() const;

    inline const Rectangle* rect() const;

    inline float span() const;

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

namespace std {

ostream& operator<<(ostream& os,
                    const mcdane::botlib::ComponentTemplate& t);

} // end of namespace std

#endif

