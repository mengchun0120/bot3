#include <utility>
#include <sstream>
#include <commonlib_exception.h>
#include <commonlib_out_utils.h>
#include <commonlib_string_utils.h>
#include <commonlib_json_utils.h>
#include <botlib_component_template.h>
#include <botlib_composite_object_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

CompositeObjectTemplate::CompositeObjectTemplate(
                                    GameObjectType t,
                                    float collideBreath,
                                    bool invincible,
                                    std::vector<Component>&& components)
    : GameObjectTemplate(t, 0.0f, collideBreath, invincible)
    , components_(std::forward<std::vector<Component>>(components))
{
    resetSpan();
}

void CompositeObjectTemplate::init(GameObjectType t,
                                   float collideBreath,
                                   bool invincible,
                                   std::vector<Component>&& components)
{
    GameObjectTemplate::init(t, 0.0f, collideBreath, invincible);
    components_ = std::move(components);
    resetSpan();
}

void CompositeObjectTemplate::resetSpan()
{
    for (std::size_t i = 0; i < components_.size(); ++i)
    {
        const Component& c = components_[i];
        float s = c.pos().norm() + c.getTemplate()->span();
        if (s >= span_)
        {
            span_ = s;
        }
    }
}

rapidjson::Value CompositeObjectTemplate::toJson(
                rapidjson::Document::AllocatorType& allocator) const
{
    using namespace rapidjson;

    Value v(kObjectType);

    v.AddMember("class", "CompositeObjectTemplate", allocator);
    v.AddMember("components", jsonVal(components_, allocator), allocator);
    v.AddMember("base", GameObjectTemplate::toJson(allocator), allocator);

    return v;
}

} // end of namespace botlib
} // end of namespace mcdane

