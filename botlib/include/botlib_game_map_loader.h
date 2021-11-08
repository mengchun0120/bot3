#ifndef INCLUDED_BOTLIB_GAME_MAP_LOADER_H
#define INCLUDED_BOTLIB_GAME_MAP_LOADER_H

#include <rapidjson/document.h>
#include <botlib_game_map.h>

namespace mcdane {
namespace botlib {

class GameMapLoader {
public:
    GameMapLoader(unsigned int poolSize,
                  float viewportWidth,
                  float viewportHeight);

    void load(GameMap& map,
              const std::string& fileName);

private:
    void loadMapDimesion(unsigned int& rows,
                         unsigned int& cols,
                         const rapidjson::Document& doc);

    void loadObjects(GameMap& map,
                     const rapidjson::Document& doc);

private:
    unsigned int poolSize_;
    float viewportWidth_;
    float viewportHeight_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

