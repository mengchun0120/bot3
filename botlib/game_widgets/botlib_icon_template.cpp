#include <commonlib_exception.h>
#include <commonlib_json_param.h>
#include <commonlib_named_map.h>
#include <commonlib_texture.h>
#include <botlib_rectangle.h>
#include <botlib_icon_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void IconTemplate::init(const rapidjson::Value &v,
                        const TextureLib &textureLib,
                        const RectLib &rectLib)
{
    std::string textureName, rectName;
    std::vector<JsonParamPtr> params{
        jsonParam(textureName, "texture", true, k_nonEmptyStrV),
        jsonParam(rectName, "rect", true, k_nonEmptyStrV)
    };

    parse(params, v);

    texture_ = textureLib.search(textureName);
    if (!texture_)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Failed to find texture " + textureName);
    }

    rect_ = rectLib.search(rectName);
    if (!rect_)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Failed to find rect " + rectName);
    }
}

} // end of namespace botlib
} // end of namespace mcdane

