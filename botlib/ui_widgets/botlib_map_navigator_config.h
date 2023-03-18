#ifndef INCLUDED_BOTLIB_MAP_NAVIGATOR_CONFIG_H
#define INCLUDED_BOTLIB_MAP_NAVIGATOR_CONFIG_H

#include <commonlib_texture.h>
#include <commonlib_color.h>
#include <botlib_polygon.h>

namespace mcdane {
namespace botlib {

class MapNavigatorConfig {
public:
    MapNavigatorConfig();

    ~MapNavigatorConfig() = default;

    void init(const std::string &fileName);

    inline const commonlib::Texture &texture() const;

    inline const commonlib::Color &activateColor() const;

    inline float radius() const;

    inline const Polygon &control(int idx) const;

private:
    void initTexture(const std::string &textureFile);

private:
    commonlib::Texture texture_;
    commonlib::Color activateColor_;
    float radius_;
    std::vector<Polygon> controls_;
};

const commonlib::Texture &MapNavigatorConfig::texture() const
{
    return texture_;
}

const commonlib::Color &MapNavigatorConfig::activateColor() const
{
    return activateColor_;
}

float MapNavigatorConfig::radius() const
{
    return radius_;
}

const Polygon &MapNavigatorConfig::control(int idx) const
{
    return controls_[idx];
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
