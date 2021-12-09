#include <botlib_missile_template.h>

namespace mcdane {
namespace botlib {

MissileTemplate::MissileTemplate(float collideBreath,
                                 float damage,
                                 float speed,
                                 std::vector<Component>&& components)
    : CompositeObjectTemplate(
        GameObjectType::MISSILE,
        collideBreath,
        false,
        std::forward<std::vector<Component>>(components))
    , damage_(damage)
    , speed_(speed)
{
}

} // end of namespace botlib
} // end of namespace mcdane

