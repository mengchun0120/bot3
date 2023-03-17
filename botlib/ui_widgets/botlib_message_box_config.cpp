#include <commonlib_log.h>
#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
#include <botlib_message_box_config.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void MessageBoxConfig::init(const std::string &configFile)
{
    rapidjson::Document doc;
    readJson(doc, configFile);

    std::vector<JsonParamPtr> params{
        jsonParam(messageMarginX_, {"messageMarginX"}, true, gt(0.0f)),
        jsonParam(messageMarginY_, {"messageMarginY"}, true, gt(0.0f)),
        jsonParam(messageHeight_, {"messageHeight"}, true, gt(0.0f)),
        jsonParam(buttonMarginY_, {"buttonMarginY"}, true, gt(0.0f)),
        jsonParam(buttonSpacing_, {"buttonSpacing"}, true, gt(0.0f)),
        jsonParam(buttonWidth_, {"buttonWidth"}, true, gt(0.0f)),
        jsonParam(buttonHeight_, {"buttonHeight"}, true, gt(0.0f)),
        jsonParam(messageBorderColor_, {"messageBorderColor"})
    };

    parse(params, doc);

    LOG_INFO << "MessageBox config initialized successfully" << LOG_END;
}

} // end of namespace botlib
} // end of namespace mcdane

