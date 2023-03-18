#ifndef INCLUDED_BOTLIB_SHOW_MAP_SCREEN_CONFIG_H
#define INCLUDED_BOTLIB_SHOW_MAP_SCREEN_CONFIG_H

#include <string>
#include <commonlib_vector.h>

namespace mcdane {
namespace botlib {

class ShowMapScreenConfig {
public:
    ShowMapScreenConfig() = default;

    void init(const std::string &cfgFile);

    inline const std::string &mapFile() const;

    void setMapFile(const std::string &fileName);

    inline float deltaPerStroke() const;

    inline const commonlib::Vector2 &navigatorPos() const;

private:
    std::string mapFile_;
    float deltaPerStroke_;
    commonlib::Vector2 navigatorPos_;
};

const std::string &ShowMapScreenConfig::mapFile() const
{
    return mapFile_;
}

float ShowMapScreenConfig::deltaPerStroke() const
{
    return deltaPerStroke_;
}

const commonlib::Vector2 &ShowMapScreenConfig::navigatorPos() const
{
    return navigatorPos_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
