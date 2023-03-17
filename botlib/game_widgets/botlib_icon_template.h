#ifndef INCLUDED_BOTLIB_ICON_TEMPLATE_H
#define INCLUDED_BOTLIB_ICON_TEMPLATE_H

#include <rapidjson/document.h>
#include <botlib_typedef.h>

namespace mcdane {
namespace botlib {

class IconTemplate {
public:
    IconTemplate() = default;

    void init(const rapidjson::Value &v,
              const TextureLib &textureLib,
              const RectLib &rectLib);

    inline const commonlib::Texture *texture() const;

    inline const Rectangle *rect() const;

private:
    const commonlib::Texture *texture_;
    const Rectangle *rect_;
};

const commonlib::Texture *IconTemplate::texture() const
{
    return texture_;
}

const Rectangle *IconTemplate::rect() const
{
    return rect_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

