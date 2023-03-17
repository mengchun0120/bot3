#include <botlib_screen_settings.h>

namespace mcdane {
namespace botlib {

void ScreenSettings::init(const std::string &startScreenCfgFile,
                          const std::string &mapFile)
{
    startScreenConfig_.init(startScreenCfgFile);
    gameScreenConfig_.init(mapFile);
}

} // end of namespace botlib
} // end of namespace mcdane

