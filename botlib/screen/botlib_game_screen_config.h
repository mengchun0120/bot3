#ifndef INCLUDED_BOTLIB_GAME_SCREEN_CONFIG_H
#define INCLUDED_BOTLIB_GAME_SCREEN_CONFIG_H

#include <string>

namespace mcdane {
namespace botlib {

class GameScreenConfig {
public:
    GameScreenConfig(const std::string& configFile);

    inline const std::string& mapFile() const;

private:
    void init(const std::string& configFile);

private:
    std::string mapFile_;
};

const std::string& GameScreenConfig::mapFile() const
{
    return mapFile_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

