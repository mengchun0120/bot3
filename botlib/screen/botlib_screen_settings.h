#ifndef INCLUDED_BOTLIB_SCREEN_SETTINGS_H
#define INCLUDED_BOTLIB_SCREEN_SETTINGS_H

#include <botlib_start_screen_config.h>
#include <botlib_game_screen_config.h>

namespace mcdane {
namespace botlib {

class ScreenSettings {
public:
    ScreenSettings() = default;

    void init(const std::string &startScreenCfgFile,
              const std::string &mapFile);

    inline const StartScreenConfig &startScreenConfig() const;

    inline const GameScreenConfig &gameScreenConfig() const;

private:
    StartScreenConfig startScreenConfig_;
    GameScreenConfig gameScreenConfig_;
};

const StartScreenConfig &ScreenSettings::startScreenConfig() const
{
    return startScreenConfig_;
}

const GameScreenConfig &ScreenSettings::gameScreenConfig() const
{
    return gameScreenConfig_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

