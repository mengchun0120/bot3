#include <commonlib_log.h>
#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
#include <botlib_label_config.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

LabelConfig::LabelConfig(const std::string configFile)
{
    rapidjson::Document doc;
    readJson(doc, configFile);

    std::vector<JsonParamPtr> params{
        jsonParam(defaultTextColor_, {"defaultTextColor"}),
        jsonParam(defaultBackColor_, {"defaultBackColor"}),
        jsonParam(defaultBorderColor_, {"defaultBorderColor"})
    };

    parse(params, doc);

    LOG_INFO << "Label config initialized successfully" << LOG_END;
}

} // end of namespace botlib
} // end of namespace mcdane

