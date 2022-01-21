#include <commonlib_exception.h>
#include <commonlib_log.h>
#include <commonlib_string_utils.h>
#include <commonlib_json_utils.h>
#include <commonlib_collide.h>
#include <botlib_game_lib.h>
#include <botlib_tile.h>
#include <botlib_missile.h>
#include <botlib_ai_robot.h>
#include <botlib_particle_effect.h>
#include <botlib_player.h>
#include <botlib_add_object_checker.h>
#include <botlib_game_map_loader.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

GameMapLoader::GameMapLoader(float viewportWidth,
                             float viewportHeight)
    : commonParams_{
        jsonParam(typeStr_, "type", true, k_nonEmptyStrV),
        jsonParam(templateStr_, "template", true, k_nonEmptyStrV),
        jsonParam(pos_, "pos", true)
      }
    , tileParams_{
        jsonParam(direction_, "direction")
      }
    , missileParams_{
        jsonParam(direction_, "direction"),
        jsonParam(sideStr_, "side")
      }
    , robotParams_{
        jsonParam(direction_, "direction"),
        jsonParam(movingEnabled_, "movingEnabled", false)
      }
{
    if (viewportWidth <= 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid viewportWidth " + stringVal(viewportWidth));
    }

    if (viewportHeight <= 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid viewportHeight " + stringVal(viewportHeight));
    }

    viewportWidth_ = viewportWidth;
    viewportHeight_ = viewportHeight;
}

void GameMapLoader::load(GameMap& map,
                         const std::string& fileName)
{
    rapidjson::Document doc;
    readJson(doc, fileName);

    loadMapDimension(map, doc);
    loadObjects(map, doc);

    LOG_DEBUG << "Loaded map " << fileName << ": " << map << LOG_END;
}

void GameMapLoader::loadMapDimension(GameMap& map,
                                     const rapidjson::Document& doc)
{
    unsigned int rows, cols;
    std::vector<JsonParamPtr> params{
        jsonParam(rows, "rows"),
        jsonParam(cols, "cols")
    };

    parse(params, doc);

    const GameLib& lib = GameLib::getInstance();

    map.init(rows, cols, viewportWidth_, viewportHeight_,
             lib.maxObjSpan(), lib.maxCollideBreath());
}

void GameMapLoader::loadObjects(GameMap& map,
                                const rapidjson::Document& doc)
{
    if (!doc.HasMember("objects"))
    {
        THROW_EXCEPT(ParseException, "Missing objects");
    }

    const rapidjson::Value& objects = doc["objects"];
    if (!objects.IsArray())
    {
        THROW_EXCEPT(ParseException, "Invalid map format");
    }

    int numObjects = objects.Capacity();
    for (int i = 0; i < numObjects; ++i)
    {
        parseAddObject(map, objects[i]);
    }
}

void GameMapLoader::parseAddObject(GameMap& map,
                                   const rapidjson::Value& v)
{
    parse(commonParams_, v);

    if (typeStr_ == "tile")
    {
        addTile(map, v);
    }
    else if (typeStr_ == "missile")
    {
        addMissile(map, v);
    }
    else if (typeStr_ == "robot")
    {
        addAIRobot(map, v);
    }
    else if (typeStr_ == "particleEffect")
    {
        addParticleEffect(map, v);
    }
    else if (typeStr_ == "player")
    {
        addPlayer(map, v);
    }
    else
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid type " + typeStr_);
    }
}

void GameMapLoader::addTile(GameMap& map,
                            const rapidjson::Value& v)
{
    const GameLib& lib = GameLib::getInstance();

    const TileTemplate* t = lib.findTileTemplate(templateStr_);
    if (!t)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Failed to find TileTemplate " + templateStr_);
    }

    bool collide = checkCollide(map, t->collideBreath());
    if (collide)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Tile " + templateStr_ + " cannot be placed in map");
    }

    parse(tileParams_, v);

    Tile* tile = new Tile();
    tile->init(t, pos_, direction_);

    map.addObj(tile);
}

void GameMapLoader::addMissile(GameMap& map,
                               const rapidjson::Value& v)
{
    const GameLib& lib = GameLib::getInstance();

    const MissileTemplate* t = lib.findMissileTemplate(templateStr_);
    if (!t)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Failed to find MissileTemplate " + templateStr_);
    }

    bool collide = checkCollide(map, t->collideBreath());
    if (collide)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Missile " + templateStr_ + " cannot be placed in map");
    }

    parse(missileParams_, v);

    Side side = strToSide(sideStr_);

    Missile* missile = new Missile();
    missile->init(t, side, pos_, direction_);

    map.addObj(missile);
}

void GameMapLoader::addAIRobot(GameMap& map,
                             const rapidjson::Value& v)
{
    const GameLib& lib = GameLib::getInstance();

    const AIRobotTemplate* t = lib.findAIRobotTemplate(templateStr_);
    if (!t)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Failed to find AIRobotTemplate " + templateStr_);
    }

    bool collide = checkCollide(map, t->collideBreath());

    if (collide)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Robot " + templateStr_ + " cannot be placed in map");
    }

    parse(robotParams_, v);

    AIRobot* robot = new AIRobot();
    robot->init(t, pos_, direction_);

    if (movingEnabled_)
    {
        robot->setMovingEnabled(true);
    }

    map.addObj(robot);
}

void GameMapLoader::addParticleEffect(GameMap& map,
                                      const rapidjson::Value& v)
{
    const GameLib& lib = GameLib::getInstance();

    const ParticleEffectTemplate* t = lib.findParticleEffectTemplate(templateStr_);
    if (!t)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Failed to find ParticleEffectTemplate " + templateStr_);
    }

    ParticleEffect* effect = new ParticleEffect();
    effect->init(t, pos_);

    map.addObj(effect);
}

void GameMapLoader::addPlayer(GameMap& map,
                              const rapidjson::Value& v)
{
    const PlayerTemplate& t = GameLib::getInstance().playerTemplate();

    bool collide = checkCollide(map, t.collideBreath());

    if (collide)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Player cannot be placed in map");
    }

    parse(robotParams_, v);

    Player* player = new Player();
    player->init(&t, pos_, direction_);

    map.addObj(player);
}

bool GameMapLoader::checkCollide(GameMap& map,
                                 float collideBreath)
{
    Region<float> r{pos_[0]-collideBreath, pos_[0]+collideBreath,
                    pos_[1]-collideBreath, pos_[1]+collideBreath};

    if (checkRectCollideBoundary(r, map.boundary()))
    {
        return true;
    }

    AddObjectChecker checker(r);
    Region<int> area = map.getCollideArea(r);
    map.accessRegion(area, checker, false);

    return checker.collide();
}

} // end of namespace botlib
} // end of namespace mcdane

