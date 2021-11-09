#include <commonlib_exception.h>
#include <commonlib_string_utils.h>
#include <commonlib_json_utils.h>
#include <botlib_game_lib.h>
#include <botlib_tile.h>
#include <botlib_game_map_loader.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

GameMapLoader::GameMapLoader(float poolSizeFactor,
                             float viewportWidth,
                             float viewportHeight)
    : params_{
          jsonParam(typeStr_, "type", true, nonempty(typeStr_)),
          jsonParam(templateStr_, "template", true, nonempty(templateStr_)),
          jsonParam(x_, "x"),
          jsonParam(y_, "y")
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

    unsigned int poolSize = static_cast<unsigned int>(floor(rows * cols * poolSizeFactor_));
    map.init(poolSize, rows, cols, viewportWidth_, viewportHeight_);
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
        THROW_EXCEPT(InvalidArgumentException, "Failed to find TileTemplate " + templateStr_);
    }

    Tile* tile = new Tile(t, x_, y_);
    map.addObj(tile);
}

} // end of namespace botlib
} // end of namespace mcdane

