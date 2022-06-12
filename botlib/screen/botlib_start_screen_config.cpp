#include <commonlib_log.h>
#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
#include <botlib_start_screen_config.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void StartScreenConfig::init(const std::string& cfgFile)
{
    rapidjson::Document doc;
    readJson(doc, cfgFile);

    std::vector<JsonParamPtr> params{
        jsonParam(buttonWidth_, "buttonWidth", true, gt(0.0f)),
        jsonParam(buttonHeight_, "buttonHeight", true, gt(0.0f)),
        jsonParam(buttonSpacing_, "buttonSpacing", true, gt(0.0f))
    };

    parse(params, doc);

    LOG_INFO << "StartScreenConfig initialized successfully" << LOG_END;
}

} // end of namespace botlib
} // end of namespace mcdane

