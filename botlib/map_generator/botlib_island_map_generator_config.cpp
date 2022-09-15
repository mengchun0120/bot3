#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
#include <botlib_island_map_generator_config.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void IslandMapGeneratorConfig::init(const std::string& fileName)
{
    rapidjson::Document doc;
    readJson(doc, fileName);

    GameMapGeneratorConfig::init(doc);

    std::vector<JsonParamPtr> params{
        jsonParam(minIslandBreath_, "minIslandBreath", true, gt(0.0f)),
        jsonParam(maxIslandBreath_, "maxIslandBreath", true, gt(0.0f)),
        jsonParam(minIslandDist_, "minIslandDist", true, gt(0.0f)),
        jsonParam(maxIslandDist_, "maxIslandDist", true, gt(0.0f))
    };

    parse(params, doc);
}

} // end of namespace botlib
} // end of namespace mcdane
