#ifndef INCLUDED_BOTLIB_GAME_SCREEN_CONFIG_H
#define INCLUDED_BOTLIB_GAME_SCREEN_CONFIG_H

#include <string>
#include <vector>
#include <commonlib_vector.h>
#include <commonlib_color.h>
#include <commonlib_texture.h>
#include <botlib_text_size.h>

namespace mcdane {
namespace botlib {

class GameLib;
class ProgressPieTemplate;

class GameScreenConfig {
public:
    GameScreenConfig() = default;

    void init(const GameLib& gameLib,
              const std::string& configFile);

    inline const std::string& mapFile() const;

    void setMapFile(const std::string& fileName);

    inline int gameObjItemPoolSize() const;

    inline int missilePoolSize() const;

    inline float goodieSpacing() const;

    inline float goodieTopMargin() const;

    inline float goodieRightMargin() const;

    inline const commonlib::Vector2& armorProgressBarMargin() const;

    inline const commonlib::Vector2& energyProgressBarMargin() const;

    inline float msgBoxWidth() const;

    inline float msgBoxHeight() const;

    inline const std::string& victoryMsg() const;

    inline const std::string& failMsg() const;

    inline const commonlib::Vector2& aiRobotCountIconMargin() const;

    inline const IconTemplate* aiRobotCountIconTemplate() const;

    inline const commonlib::Vector2& aiRobotCountTextMargin() const;

    inline TextSize aiRobotCountTextSize() const;

    inline const commonlib::Color& aiRobotCountTextColor() const;

    inline const ProgressPieTemplate* goodiePieTemplate(int idx) const;

private:
    void initGoodiePieTemplates(
                    const std::vector<std::string>& goodiePieNames,
                    const GameLib& gameLib);

private:
    std::string mapFile_;
    int gameObjItemPoolSize_;
    int missilePoolSize_;
    float goodieSpacing_;
    float goodieTopMargin_;
    float goodieRightMargin_;
    commonlib::Vector2 armorProgressBarMargin_;
    commonlib::Vector2 energyProgressBarMargin_;
    float msgBoxWidth_;
    float msgBoxHeight_;
    std::string victoryMsg_;
    std::string failMsg_;
    commonlib::Vector2 aiRobotCountIconMargin_;
    const IconTemplate* aiRobotCountIconTemplate_;
    commonlib::Vector2 aiRobotCountTextMargin_;
    TextSize aiRobotCountTextSize_;
    commonlib::Color aiRobotCountTextColor_;
    std::vector<const ProgressPieTemplate*> goodiePieTemplates_;
};

const std::string& GameScreenConfig::mapFile() const
{
    return mapFile_;
}

int GameScreenConfig::gameObjItemPoolSize() const
{
    return gameObjItemPoolSize_;
}

int GameScreenConfig::missilePoolSize() const
{
    return missilePoolSize_;
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

float GameScreenConfig::msgBoxWidth() const
{
    return msgBoxWidth_;
}

float GameScreenConfig::msgBoxHeight() const
{
    return msgBoxHeight_;
}

const std::string& GameScreenConfig::victoryMsg() const
{
    return victoryMsg_;
}

const std::string& GameScreenConfig::failMsg() const
{
    return failMsg_;
}

const commonlib::Vector2& GameScreenConfig::aiRobotCountIconMargin() const
{
    return aiRobotCountIconMargin_;
}

const IconTemplate* GameScreenConfig::aiRobotCountIconTemplate() const
{
    return aiRobotCountIconTemplate_;
}

const commonlib::Vector2& GameScreenConfig::aiRobotCountTextMargin() const
{
    return aiRobotCountTextMargin_;
}

TextSize GameScreenConfig::aiRobotCountTextSize() const
{
    return aiRobotCountTextSize_;
}

const commonlib::Color& GameScreenConfig::aiRobotCountTextColor() const
{
    return aiRobotCountTextColor_;
}

const ProgressPieTemplate* GameScreenConfig::goodiePieTemplate(int idx) const
{
    return goodiePieTemplates_[idx];
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

