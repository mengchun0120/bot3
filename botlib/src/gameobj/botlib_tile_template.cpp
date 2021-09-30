#include <commonlib_json_param.h>
#include <botlib_tile_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

TileTemplate::TileTemplate(const rapdidjson::Value& v)
    : GameObjectTemplate(GameObjectType::TILE, v)
{
    init(v);
}

void TileTemplate::init(const rapdidjson::Value& v)
{
    float width, height;
    std::vector<JsonParamPtr> params{
        jsonParam(width, "width", true, gt(width, 0.0f)),
        jsonParam(height, "height", true, gt(height, 0.0f)),
        jsonParam(color_, "color"),
        jsonParam(hp_, "hp", true, ge(hp_, 0.0f))
    };

    parse(params, v);
}

} // end of namespace botlib
} // end of namespace mcdane

