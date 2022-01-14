#include <utility>
#include <commonlib_exception.h>
#include <commonlib_out_utils.h>
#include <commonlib_string_utils.h>
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

} // end of namespace botlib
} // end of namespace mcdane

namespace std {

ostream& operator<<(ostream& os,
                    const mcdane::botlib::CompositeObjectTemplate& t)
{
    using namespace mcdane::botlib;

    os << "CompositeObjectTemplate(" << &t
       << ", components=" << t.components()
       << ", Base=" << static_cast<const GameObjectTemplate&>(t)
       << ")";

    return os;
}

} // end of namespace std


