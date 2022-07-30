#ifndef INCLUDED_BOTLIB_GAME_SCREEN_CONFIG_H
#define INCLUDED_BOTLIB_GAME_SCREEN_CONFIG_H

#include <string>
#include <commonlib_vector.h>

namespace mcdane {
namespace botlib {

class GameScreenConfig {
public:
    GameScreenConfig() = default;

    void init(const std::string& configFile);

    inline const std::string& mapFile() const;

    inline int dumperPoolSize() const;

    inline float goodieSpacing() const;

    inline float goodieTopMargin() const;

    inline float goodieRightMargin() const;

    inline const commonlib::Vector2& armorProgressBarMargin() const;

    inline const commonlib::Vector2& energyProgressBarMargin() const;

private:
    std::string mapFile_;
    int dumperPoolSize_;
    float goodieSpacing_;
    float goodieTopMargin_;
    float goodieRightMargin_;
    commonlib::Vector2 armorProgressBarMargin_;
    commonlib::Vector2 energyProgressBarMargin_;
};

const std::string& GameScreenConfig::mapFile() const
{
    return mapFile_;
}

int GameScreenConfig::dumperPoolSize() const
{
    return dumperPoolSize_;
}

float GameScreenConfig::goodieSpacing() const
{
    return goodieSpacing_;
}

float GameScreenConfig::goodieTopMargin() const
{
    return goodieTopMargin_;
}

float GameScreenConfig::goodieRightMargin() const
{
    return goodieRightMargin_;
}

const commonlib::Vector2& GameScreenConfig::armorProgressBarMargin() const
{
    return armorProgressBarMargin_;
}

const commonlib::Vector2& GameScreenConfig::energyProgressBarMargin() const
{
    return energyProgressBarMargin_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

