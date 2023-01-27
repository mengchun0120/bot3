#ifndef INCLUDED_BOTLIB_GAME_MAP_LOADER_H
#define INCLUDED_BOTLIB_GAME_MAP_LOADER_H

#include <rapidjson/document.h>
#include <commonlib_json_param.h>
#include <botlib_game_map.h>
#include <botlib_typedef.h>

namespace mcdane {
namespace botlib {

class GameObjectFactory;

class GameMapLoader {
public:
    GameMapLoader(float viewportWidth,
                  float viewportHeight,
                  GameObjectFactory& factory);

    void load(GameMap& map,
              const std::string& fileName);

private:
    void loadMapDimension(GameMap& map,
                          const rapidjson::Document& doc);

    void loadObjects(GameMap& map,
                     const rapidjson::Document& doc);

    void parseAddObject(GameMap& map,
                        const rapidjson::Value& v);

    void addTile(GameMap& map,
                 const rapidjson::Value& v);

    void addGoodie(GameMap& map,
                   const rapidjson::Value& v);

    void addMissile(GameMap& map,
                    const rapidjson::Value& v);

    void addAIRobot(GameMap& map,
                    const rapidjson::Value& v);

    void addParticleEffect(GameMap& map,
                           const rapidjson::Value& v);

    void addPlayer(GameMap& map,
                   const rapidjson::Value& v);

    void calculatePlayerGoodiePos(float& goodieY,
                                  float& goodieStartX,
                                  float& goodieSpacing);

private:
    float viewportWidth_;
    float viewportHeight_;
    GameObjectFactory& factory_;
    std::string typeStr_;
    std::string templateStr_;
    commonlib::Vector2 pos_;
    commonlib::Vector2 direction_;
    std::string sideStr_;
    std::vector<commonlib::JsonParamPtr> commonParams_;
    std::vector<commonlib::JsonParamPtr> tileParams_;
    std::vector<commonlib::JsonParamPtr> goodieParams_;
    std::vector<commonlib::JsonParamPtr> missileParams_;
    std::vector<commonlib::JsonParamPtr> robotParams_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

