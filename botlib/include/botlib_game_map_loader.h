#ifndef INCLUDED_BOTLIB_GAME_MAP_LOADER_H
#define INCLUDED_BOTLIB_GAME_MAP_LOADER_H

#include <rapidjson/document.h>
#include <commonlib_json_param.h>
#include <botlib_game_map.h>

namespace mcdane {
namespace botlib {

class GameMapLoader {
public:
    GameMapLoader(float poolSizeFactor,
                  float viewportWidth,
                  float viewportHeight);

    void load(GameMap& map,
              const std::string& fileName);

private:
    void loadMapDimension(GameMap& map,
                          const rapidjson::Document& doc);

    void loadObjects(GameMap& map,
                     const rapidjson::Document& doc);

    void parseAddObject(GameMap& map,
                        const rapidjson::Value& v);

    void addTile(GameMap& map);

private:
    float poolSizeFactor_;
    float viewportWidth_;
    float viewportHeight_;
    std::string typeStr_;
    std::string templateStr_;
    commonlib::Vector2 pos_;
    std::vector<mcdane::commonlib::JsonParamPtr> params_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif
