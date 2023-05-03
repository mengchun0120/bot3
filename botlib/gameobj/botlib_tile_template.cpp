#include <utility>
#include <commonlib_json_param.h>
#include <botlib_tile_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

TileTemplate::TileTemplate()
    : hp_(0.0f)
    , dyingDuration_(0.0f)
    , touchSpan_(0.0f)
{
}

void TileTemplate::init(
    const std::string &name,
    const rapidjson::Value &v,
    const ComponentTemplateLib &componentTemplateLib)
{
    std::vector<JsonParamPtr> params{
        jsonParam(hp_, "hp", true, gt(0.0f)),
        jsonParam(dyingDuration_, "dyingDuration", true, gt(0.0f)),
        jsonParam(touchSpan_, "touchSpan", true, gt(0.0f)),
    };

    parse(params, v);
    CompositeObjectTemplate::init(GameObjectType::TILE, name,
                                  v, componentTemplateLib);
}

} // end of namespace botlib
} // end of namespace mcdane

