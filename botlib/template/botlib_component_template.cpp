#include <cmath>
#include <sstream>
#include <commonlib_exception.h>
#include <commonlib_json_param.h>
#include <commonlib_texture.h>
#include <commonlib_named_map.h>
#include <botlib_rectangle.h>
#include <botlib_component_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void ComponentTemplate::init(const rapidjson::Value& v,
                             const TextureLib& textureLib,
                             const RectLib& rectLib)
{
    std::string typeStr, textureName, rectName;
    std::vector<JsonParamPtr> params{
        jsonParam(typeStr, "type", true, k_nonEmptyStrV),
        jsonParam(textureName, "texture", true, k_nonEmptyStrV),
        jsonParam(rectName, "rect", true, k_nonEmptyStrV),
        jsonParam(firePos_, "firePos", false)
    };

    parse(params, v);

    type_ = toComponentType(typeStr);

    texture_ = textureLib.search(textureName);
    if (!texture_)
    {
        THROW_EXCEPT(ParseException, "Failed to find texture " + textureName);
    }

    rect_ = rectLib.search(rectName);
    if (!rect_)
    {
        THROW_EXCEPT(ParseException, "Failed to find rectangle " + rectName);
    }

    resetSpan();
}

void ComponentTemplate::resetSpan()
{
    span_ = static_cast<float>(sqrt(rect_->width() * rect_->width() +
                                    rect_->height() * rect_->height()) / 2.0);
}

} // end of namespace botlib
} // end of namespace mcdane

