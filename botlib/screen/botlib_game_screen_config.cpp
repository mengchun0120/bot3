#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
#include <commonlib_file_utils.h>
#include <botlib_app_config.h>
#include <botlib_context.h>
#include <botlib_game_screen_config.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void GameScreenConfig::init(const GameLib& gameLib,
                            const std::string& configFile)
{
    rapidjson::Document doc;
    std::string aiRobotCountIconName;
    std::string aiRobotCountTextSizeStr;
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
        jsonParam(failMsg_, {"messageBox", "failMsg"}, true, k_nonEmptyStrV),
        jsonParam(aiRobotCountIconMargin_, {"aiRobotCount", "iconMargin"}),
        jsonParam(aiRobotCountIconName, {"aiRobotCount", "icon"},
                  true, k_nonEmptyStrV),
        jsonParam(aiRobotCountTextMargin_, {"aiRobotCount", "textMargin"}),
        jsonParam(aiRobotCountTextSizeStr, {"aiRobotCount", "textSize"}, true,
                  k_nonEmptyStrV),
        jsonParam(aiRobotCountTextColor_, {"aiRobotCount", "textColor"})
    };

    parse(params, doc);

    aiRobotCountIconTemplate_ = gameLib.findIconTemplate(aiRobotCountIconName);
    if (!aiRobotCountIconTemplate_)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Failed to find texture " + aiRobotCountIconName);
    }


    aiRobotCountTextSize_ = toTextSize(aiRobotCountTextSizeStr);

    const AppConfig& cfg = AppConfig::instance();

    mapFile_ = constructPath({cfg.mapDir(), mapFile_});

    LOG_INFO << "GameScreenConfig initialized successfully" << LOG_END;
}

void GameScreenConfig::setMapFile(const std::string& fileName)
{
    const AppConfig& cfg = AppConfig::instance();
    mapFile_ = constructPath({cfg.mapDir(), fileName});
}

} // end of namespace botlib
} // end of namespace mcdane

