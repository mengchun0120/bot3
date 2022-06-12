#include <commonlib_log.h>
#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
#include <botlib_context.h>
#include <botlib_hp_indicator_config.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void HPIndicatorConfig::init(const std::string& fileName)
{
    rapidjson::Document doc;
    readJson(doc, fileName);

    std::string textSizeStr;
    std::vector<JsonParamPtr> params{
        jsonParam(textSizeStr, {"textSize"}, true, k_nonEmptyStrV),
        jsonParam(color_, {"color"}, true)
    };

    parse(params, doc);

    textSize_ = toTextSize(textSizeStr);
    initSize();
}

void HPIndicatorConfig::initSize()
{
    Graphics& g = Context::graphics();

    LOG_INFO << "textSys=" << &(g.textSys()) << LOG_END;

    halfHeight_ = g.textSys().getHeight(textSize_) / 2.0f;
}

} // end of namespace botlib
} // end of namespace mcdane

