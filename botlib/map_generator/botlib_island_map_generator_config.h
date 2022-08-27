#ifndef INCLUDED_BOTLIB_ISLAND_MAP_GENERTOR_CONFIG_H
#define INCLUDED_BOTLIB_ISLAND_MAP_GENERTOR_CONFIG_H

#include <botlib_game_map_generator_config.h>

namespace mcdane {
namespace botlib {

class IslandMapGeneratorConfig: public GameMapGeneratorConfig {
public:
    IslandMapGeneratorConfig() = default;

    void init(const std::string& fileName);

    inline float minIslandBreath() const;

    inline float maxIslandBreath() const;

    inline float minIslandDist() const;

    inline float maxIslandDist() const;

    inline float minMargin() const;

    inline float maxMargin() const;

private:
    float minIslandBreath_;
    float maxIslandBreath_;
    float minIslandDist_;
    float maxIslandDist_;
    float minMargin_;
    float maxMargin_;
};

float IslandMapGeneratorConfig::minIslandBreath() const
{
    return minIslandBreath_;
}

float IslandMapGeneratorConfig::maxIslandBreath() const
{
    return maxIslandBreath_;
}

float IslandMapGeneratorConfig::minIslandDist() const
{
    return minIslandDist_;
}

float IslandMapGeneratorConfig::maxIslandDist() const
{
    return maxIslandDist_;
}

float IslandMapGeneratorConfig::minMargin() const
{
    return minMargin_;
}

float IslandMapGeneratorConfig::maxMargin() const
{
    return maxMargin_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
