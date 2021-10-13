#ifndef INCLUDED_BOTLIB_GAME_UTILS_H
#define INCLUDED_BOTLIB_GAME_UTILS_H

#include <string>
#include <botlib_game_map.h>

namespace mcdane {
namespace botlib {

void loadGameMap(GameMap& map,
                 const std::string& fileName);

} // end of namespace botlib
} // end of namespace mcdane

#endif

