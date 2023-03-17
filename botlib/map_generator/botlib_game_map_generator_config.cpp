#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_json_param.h>
#include <botlib_game_map_generator_config.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void GameMapGeneratorConfig::init(const rapidjson::Value &v)
{
    constexpr int MIN_CELL_COUNT = 40;
    constexpr int MAX_CELL_COUNT = 128;

    std::vector<JsonParamPtr> params{
        jsonParam(rowCount_, "rowCount", true,
                  ge(MIN_CELL_COUNT) && le(MAX_CELL_COUNT)),
        jsonParam(colCount_, "colCount", true,
                  ge(MIN_CELL_COUNT) && le(MAX_CELL_COUNT)),
        jsonParam(aiRobotCount_, "aiRobotCount", true, gt(0))
    };

    parse(params, v);
}

} // end of namespace botlib
} // end of namespace mcdane
