#ifndef INCLUDED_BOTLIB_GAME_MAP_GENERATOR_CONFIG_H
#define INCLUDED_BOTLIB_GAME_MAP_GENERATOR_CONFIG_H

#include <rapidjson/document.h>

namespace mcdane {
namespace botlib {

class GameMapGeneratorConfig {
public:
    GameMapGeneratorConfig() = default;

    virtual ~GameMapGeneratorConfig() = default;

    void init(const rapidjson::Value& v);

    inline int rowCount() const;

    inline int colCount() const;

    inline int aiRobotCount() const;

protected:
    int rowCount_;
    int colCount_;
    int aiRobotCount_;
};

int GameMapGeneratorConfig::rowCount() const
{
    return rowCount_;
}

int GameMapGeneratorConfig::colCount() const
{
    return colCount_;
}

int GameMapGeneratorConfig::aiRobotCount() const
{
    return aiRobotCount_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
