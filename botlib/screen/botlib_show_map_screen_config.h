#ifndef INCLUDED_BOTLIB_SHOW_MAP_SCREEN_CONFIG_H
#define INCLUDED_BOTLIB_SHOW_MAP_SCREEN_CONFIG_H

#include <string>

namespace mcdane {
namespace botlib {

class ShowMapScreenConfig {
public:
    ShowMapScreenConfig() = default;

    void init(const std::string& cfgFile);

    inline const std::string& mapFile() const;

    void setMapFile(const std::string& fileName);

    inline float deltaPerStroke() const;

private:
    std::string mapFile_;
    float deltaPerStroke_;
};

const std::string& ShowMapScreenConfig::mapFile() const
{
    return mapFile_;
}

float ShowMapScreenConfig::deltaPerStroke() const
{
    return deltaPerStroke_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
