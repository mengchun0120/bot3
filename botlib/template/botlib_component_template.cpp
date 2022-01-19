#include <cmath>
#include <sstream>
#include <commonlib_exception.h>
#include <botlib_component_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

ComponentTemplate::ComponentTemplate(const Texture* texture,
                                     const Rectangle* rect)
{
    init(texture, rect);
}

void ComponentTemplate::init(const commonlib::Texture* texture,
                             const Rectangle* rect)
{
    if (!texture)
    {
        THROW_EXCEPT(InvalidArgumentException, "texture is null");
    }

    if (!rect)
    {
        THROW_EXCEPT(InvalidArgumentException, "rect is null");
    }

    texture_ = texture;
    rect_ = rect;
    span_ = static_cast<float>(sqrt(rect_->width() * rect_->width() +
                                    rect_->height() * rect_->height()) / 2.0);
}

std::string ComponentTemplate::toString() const
{
    std::ostringstream oss;

    oss << "ComponentTemplate(texture=" << texture_->toString()
        << ", rect=" << rect_->toString()
        << ", Base=" << Object::toString()
        << ")";

    return oss.str();
}

rapidjson::Value ComponentTemplate::toJson(
                rapidjson::Document::AllocatorType& allocator) const
{
    using namespace rapidjson;

    Value v(kObjectType);

    v.AddMember("class", "ComponentTemplate", allocator);
    v.AddMember("texture", texture_->toJson(allocator), allocator);
    v.AddMember("rect", rect_->toJson(allocator), allocator);
    v.AddMember("base", Object::toJson(allocator), allocator);

    return v;
}

} // end of namespace botlib
} // end of namespace mcdane

