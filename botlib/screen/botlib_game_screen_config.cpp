#include <commonlib_log.h>
#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
#include <commonlib_file_utils.h>
#include <botlib_app_config.h>
#include <botlib_game_screen_config.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void GameScreenConfig::init(const std::string& configFile)
{
    rapidjson::Document doc;
    readJson(doc, configFile);

    std::vector<JsonParamPtr> params{
        jsonParam(mapFile_, "mapFile", true, k_nonEmptyStrV),
        jsonParam(dumperPoolSize_, "dumperPoolSize", true, gt(0)),
        jsonParam(goodieSpacing_, "goodieSpacing", true, gt(0.0f)),
        jsonParam(goodieTopMargin_, "goodieTopMargin", true, gt(0.0f)),
        jsonParam(goodieRightMargin_, "goodieRightMargin", true, gt(0.0f)),
        jsonParam(armorProgressBarMargin_, "armorProgressBarMargin"),
        jsonParam(energyProgressBarMargin_, "energyProgressBarMargin"),
        jsonParam(msgBoxWidth_, {"messageBox", "width"}, true, gt(0.0f)),
        jsonParam(msgBoxHeight_, {"messageBox", "height"}, true, gt(0.0f)),
        jsonParam(victoryMsg_, {"messageBox", "victoryMsg"}, true, k_nonEmptyStrV),
        jsonParam(failMsg_, {"messageBox", "failMsg"}, true, k_nonEmptyStrV)
    };

    parse(params, doc);

    const AppConfig& cfg = AppConfig::instance();

    mapFile_ = constructPath({cfg.mapDir(), mapFile_});

    LOG_INFO << "GameScreenConfig initialized successfully" << LOG_END;
}

} // end of namespace botlib
} // end of namespace mcdane

