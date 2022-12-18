#ifndef INCLUDED_BOTLIB_GAME_CONFIG_H
#define INCLUDED_BOTLIB_GAME_CONFIG_H

#include <string>

namespace mcdane {
namespace botlib {

class GameConfig {
public:
    GameConfig();

    void init(const std::string& cfgFile);

    inline bool showHPIndicator() const;

private:
    bool showHPIndicator_;
};

bool GameConfig::showHPIndicator() const
{
    return showHPIndicator_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
