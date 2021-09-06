#ifndef INCLUDED_BOTLIB_BUTTON_CONFIG_H
#define INCLUDED_BOTLIB_BUTTON_CONFIG_H

#include <string>
#include <commonlib_vector.h>
#include <commonlib_texture.h>

namespace mcdane {
namespace botlib {

class ButtonConfig {
public:
    ButtonConfig() = default;

    ~ButtonConfig() = default;

    void load(const std::string& configFile,
              const std::string& appDir);

    inline const commonlib::Color& normalTextColor();

    inline const commonlib::Color& hoverTextColor();

    inline const commonlib::Color& pressTextColor();

    inline const commonlib::Texture& texture();

private:
    commonlib::Color normalTextColor_;
    commonlib::Color hoverTextColor_;
    commonlib::Color pressTextColor_;
    commonlib::Texture texture_;
};

const commonlib::Color& ButtonConfig::normalTextColor()
{
    return normalTextColor_;
}

const commonlib::Color& ButtonConfig::hoverTextColor()
{
    return hoverTextColor_;
}

const commonlib::Color& ButtonConfig::pressTextColor()
{
    return pressTextColor_;
}

const commonlib::Texture& ButtonConfig::texture()
{
    return texture_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

