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

ComponentTemplate::ComponentTemplate(const Texture* texture1,
                                     const Rectangle* rect1)
{
    init(texture1, rect1);
}

void ComponentTemplate::init(const Texture* texture1,
                             const Rectangle* rect1)
{
    if (!texture1)
    {
        THROW_EXCEPT(InvalidArgumentException, "texture is null");
    }

    if (!rect1)
    {
        THROW_EXCEPT(InvalidArgumentException, "rect is null");
    }

    texture_ = texture1;
    rect_ = rect1;
    resetSpan();
}

void ComponentTemplate::init(const rapidjson::Value& v,
                             const TextureLib& textureLib,
                             const RectLib& rectLib)
{
    std::string textureName, rectName;
    std::vector<JsonParamPtr> params{
        jsonParam(textureName, "texture", true, k_nonEmptyStrV),
        jsonParam(rectName, "rect", true, k_nonEmptyStrV)
    };

    parse(params, v);

    const Texture* texture1 = textureLib.search(textureName);
    if (!texture1)
    {
        THROW_EXCEPT(ParseException, "Failed to find texture " + textureName);
    }

    const Rectangle* rect1 = rectLib.search(rectName);
    if (!rect1)
    {
        THROW_EXCEPT(ParseException, "Failed to find rectangle " + rectName);
    }

    init(texture1, rect1);

    NamedObject::init(v, true);
}

rapidjson::Value ComponentTemplate::toJson(
                rapidjson::Document::AllocatorType& allocator) const
{
    using namespace rapidjson;

    Value v(kObjectType);

    v.AddMember("class", "ComponentTemplate", allocator);
    v.AddMember("texture", texture_->id(), allocator);
    v.AddMember("rect", rect_->id(), allocator);
    v.AddMember("base", Object::toJson(allocator), allocator);

    return v;
}

void ComponentTemplate::resetSpan()
{
    span_ = static_cast<float>(sqrt(rect_->width() * rect_->width() +
                                    rect_->height() * rect_->height()) / 2.0);
}

} // end of namespace botlib
} // end of namespace mcdane

