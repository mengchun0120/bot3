#include <commonlib_log.h>
#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
#include <commonlib_file_utils.h>
#include <botlib_app_config.h>
#include <botlib_show_map_screen_config.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void ShowMapScreenConfig::init(const std::string &cfgFile)
{
    rapidjson::Document doc;
    readJson(doc, cfgFile);

    std::vector<JsonParamPtr> params{
        jsonParam(mapFile_, "mapFile", false, k_nonEmptyStrV),
        jsonParam(deltaPerStroke_, "deltaPerStroke", true, gt(0.0f))
    };

    parse(params, doc);

    const AppConfig &cfg = AppConfig::instance();

    mapFile_ = constructPath({cfg.mapDir(), mapFile_});

    LOG_INFO << "ShowMapScreenConfig initialized successfully" << LOG_END;
}

void ShowMapScreenConfig::setMapFile(const std::string &fileName)
{
    const AppConfig &cfg = AppConfig::instance();

    mapFile_ = constructPath({cfg.mapDir(), fileName});
}

} // end of namespace botlib
} // end of namespace mcdane

