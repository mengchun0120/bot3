#include <commonlib_exception.h>
#include <commonlib_log.h>
#include <commonlib_string_utils.h>
#include <commonlib_json_utils.h>
#include <commonlib_collide.h>
#include <botlib_game_lib.h>
#include <botlib_tile.h>
#include <botlib_ai_robot.h>
#include <botlib_add_object_checker.h>
#include <botlib_game_map_loader.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

GameMapLoader::GameMapLoader(float poolSizeFactor,
                             float viewportWidth,
                             float viewportHeight)
    : params_{
          jsonParam(typeStr_, "type", true, k_nonEmptyStrV),
          jsonParam(templateStr_, "template", true, k_nonEmptyStrV),
          jsonParam(pos_, "pos"),
          jsonParam(direction_, "direction")
      }
{
    if (poolSizeFactor <= 0.0f || poolSizeFactor > 1.0f)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid poolSizeFactor " + toString(poolSizeFactor));
    }

    if (viewportWidth <= 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid viewportWidth " + toString(viewportWidth));
    }

    if (viewportHeight <= 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Invalid viewportHeight " + toString(viewportHeight));
    }

    poolSizeFactor_ = poolSizeFactor;
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

    unsigned int poolSize = getPoolSize(rows, cols);
    const GameLib& lib = GameLib::getInstance();

    map.init(poolSize, rows, cols, viewportWidth_, viewportHeight_,
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
    parse(params_, v);

    if (typeStr_ == "tile")
    {
        addTile(map);
    }
    else if(typeStr_ == "robot")
    {
        addRobot(map);
    }
    else
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid type " + typeStr_);
    }
}

void GameMapLoader::addTile(GameMap& map)
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

    Tile* tile = new Tile();
    tile->init(t, pos_, direction_);

    map.addObj(tile);
}

void GameMapLoader::addRobot(GameMap& map)
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

    AIRobot* robot = new AIRobot();
    robot->init(t, pos_, direction_);

    map.addObj(robot);
}

unsigned int GameMapLoader::getPoolSize(unsigned int rows,
                                        unsigned int cols)
{
    return static_cast<unsigned int>(floor(rows * cols * poolSizeFactor_));
}

bool GameMapLoader::checkCollide(GameMap& map,
                                 float collideBreath)
{
    using namespace std::placeholders;

    static AddObjectChecker checker;
    static GameMap::Accessor accessor = std::bind(&AddObjectChecker::run,
                                                  &checker, _1);

    Region<float> r{pos_[0]-collideBreath, pos_[0]+collideBreath,
                    pos_[1]-collideBreath, pos_[1]+collideBreath};

    if (checkRectCollideBoundary(r, map.boundary()))
    {
        return true;
    }

    checker.reset(r);
    Region<int> area = map.getCollideArea(r);
    map.accessRegion(area, accessor);

    return checker.collide();
}

} // end of namespace botlib
} // end of namespace mcdane

