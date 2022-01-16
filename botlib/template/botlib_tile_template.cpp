#include <utility>
#include <sstream>
#include <commonlib_exception.h>
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
}

void TileTemplate::init(float collideBreath,
                        float hp,
                        bool invincible,
                        std::vector<Component>&& components)
{
    CompositeObjectTemplate::init(GameObjectType::TILE,
                                  collideBreath,
                                  invincible,
                                  std::forward<std::vector<Component>>(components));
    hp_ = hp;
}

std::string TileTemplate::toString() const
{
    std::ostringstream oss;

    oss << "TileTemplate(hp=" << hp_
       << ", Base=" << CompositeObjectTemplate::toString()
       << ")";

    return oss.str();
}

} // end of namespace botlib
} // end of namespace mcdane

