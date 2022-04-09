#include <commonlib_log.h>
#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
#include <commonlib_file_utils.h>
#include <botlib_app_config.h>
#include <botlib_game_screen_config.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

GameScreenConfig::GameScreenConfig(const std::string& configFile)
{
    init(configFile);
}

void GameScreenConfig::init(const std::string& configFile)
{
    rapidjson::Document doc;
    readJson(doc, configFile);

    std::vector<JsonParamPtr> params{
        jsonParam(mapFile_, {"mapFile"}, true, k_nonEmptyStrV)
    };

    parse(params, doc);

    const AppConfig& cfg = AppConfig::instance();

    mapFile_ = constructPath({cfg.mapDir(), mapFile_});

    LOG_INFO << "GameScreenConfig initialized successfully" << LOG_END;
}

} // end of namespace botlib
} // end of namespace mcdane

