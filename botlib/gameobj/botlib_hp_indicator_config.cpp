#include <commonlib_log.h>
#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
#include <botlib_context.h>
#include <botlib_hp_indicator_config.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

HPIndicatorConfig::HPIndicatorConfig(Graphics& g,
                                     const std::string& fileName)
{
    init(g, fileName);
}

const commonlib::Color* HPIndicatorConfig::color(float hpPercent) const
{
    unsigned int level;
    for (level = 0; level < levels_.size(); ++level)
    {
        if (hpPercent >= levels_[level])
        {
            break;
        }
    }

    return &colors_[level];
}

void HPIndicatorConfig::init(Graphics& g,
                             const std::string& fileName)
{
    rapidjson::Document doc;
    readJson(doc, fileName);

    std::string textSizeStr;
    std::vector<JsonParamPtr> params{
        jsonParam(textSizeStr, {"textSize"}, true, k_nonEmptyStrV),
        jsonParam(levels_, {"levels"}, true, nonEmptyVec<float>()),
        jsonParam(colors_, {"colors"}, true, nonEmptyVec<Color>())
    };

    parse(params, doc);

    if (levels_.size() != colors_.size())
    {
        THROW_EXCEPT(ParseException, "levels' size doesn't match colors");
    }

    textSize_ = toTextSize(textSizeStr);
    initSize(g);
}

void HPIndicatorConfig::initSize(Graphics& g)
{
    halfHeight_ = g.textSys().getHeight(textSize_) / 2.0f;
}

} // end of namespace botlib
} // end of namespace mcdane

