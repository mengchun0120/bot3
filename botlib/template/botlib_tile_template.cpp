#include <utility>
#include <commonlib_json_param.h>
#include <botlib_tile_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void TileTemplate::init(
    const rapidjson::Value& v,
    const ComponentTemplateLib& componentTemplateLib)
{
    std::vector<JsonParamPtr> params{
        jsonParam(hp_, "hp", true, gt(0.0f)),
        jsonParam(dyingDuration_, "dyingDuration", true, gt(0.0f))
    };

    parse(params, v);
    CompositeObjectTemplate::init(GameObjectType::TILE, v, componentTemplateLib);
}

} // end of namespace botlib
} // end of namespace mcdane

