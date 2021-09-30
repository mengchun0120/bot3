#include <commonlib_json_param.h>
#include <commonlib_file_utils.h>
#include <botlib_tile_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

TileTemplate::TileTemplate(const rapidjson::Value& v,
                           const std::string& picDir)
    : GameObjectTemplate(GameObjectType::TILE, v)
{
    init(v, picDir);
}

void TileTemplate::init(const rapidjson::Value& v,
                        const std::string& picDir)
{
    float width, height;
    std::string textureFile;

    std::vector<JsonParamPtr> params{
        jsonParam(width, {"width"}, true, gt(width, 0.0f)),
        jsonParam(height, {"height"}, true, gt(height, 0.0f)),
        jsonParam(textureFile, {"texture"}, true, nonempty(textureFile)),
        jsonParam(hp_, {"hp"}, true, ge(hp_, 0.0f))
    };

    parse(params, v);

    rect_.load(width, height, TexRectangle());

    textureFile = constructPath({picDir, textureFile});
    texture_.init(textureFile);
}

} // end of namespace botlib
} // end of namespace mcdane

