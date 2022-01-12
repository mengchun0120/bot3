#include <utility>
#include <commonlib_exception.h>
#include <commonlib_string_utils.h>
#include <botlib_tile_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

TileTemplate::TileTemplate(float collideBreath,
                           float hp,
                           bool invincible,
                           std::vector<Component>&& components)
    : CompositeObjectTemplate(GameObjectType::TILE,
                              collideBreath,
                              invincible,
                              std::forward<std::vector<Component>>(components))
    , hp_(hp)
{
    if (hp_ < 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid hp " + toString(hp_));
    }
}

} // end of namespace botlib
} // end of namespace mcdane

