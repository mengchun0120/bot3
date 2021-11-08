#include <commonlib_exception.h>
#include <commonlib_string_utils.h>
#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
#include <botlib_game_lib.h>
#include <botlib_game_map_loader.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

GameMapLoader::GameMapLoader(unsigned int poolSize,
                             float viewportWidth,
                             float viewportHeight)
{
    if (poolSize == 0)
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid poolSize");
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

    poolSize_ = poolSize;
    viewportWidth_ = viewportWidth;
    viewportHeight_ = viewportHeight;
}

void GameMapLoader::load(GameMap& map,
                         const std::string& fileName)
{
    rapidjson::Document doc;
    readJson(doc, fileName);

    unsigned int rows, cols;
    loadMapDimensions(rows, cols, doc);

    map.init(poolSize_, rows, cols, viewportWidth_, viewportHeight_);
    loadObjects(map, doc);
}

void GameMapLoader::loadMapDimesion(unsigned int& rows,
                                    unsigned int& cols,
                                    const rapidjson::Document& doc)
{
    std::vector<JsonParamPtr> params{
        jsonParam(rows, "rows", true, ge(rows, GameMap::k_minRows)),
        jsonParam(cols, "cols", true, ge(cols, GameMap::k_minCols))
    };

    parse(params, doc);
}

void GameMapLoader::loadObjects(GameMap& map,
                                const rapidjson::Document& doc)
{
    if (!doc.HasMember("objects"))
    {
        THROW_EXCEPT(ParseException, "Missing objects");
    }

    rapidjson::Value objects = doc["objects"];
    if (!objects.IsArray())
    {
        THROW_EXCEPT(ParseException, "Invalid map format");
    }


}

} // end of namespace botlib
} // end of namespace mcdane

