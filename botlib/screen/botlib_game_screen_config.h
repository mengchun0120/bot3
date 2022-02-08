#ifndef INCLUDED_BOTLIB_GAME_SCREEN_CONFIG_H
#define INCLUDED_BOTLIB_GAME_SCREEN_CONFIG_H

#include <string>

namespace mcdane {
namespace botlib {

class GameScreenConfig {
public:
    GameScreenConfig() = default;

    void init(const std::string& mapFile1);

    inline const std::string& mapFile() const;

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

