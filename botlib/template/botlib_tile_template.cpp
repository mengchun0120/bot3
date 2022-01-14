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

} // end of namespace botlib
} // end of namespace mcdane

namespace std {

ostream& operator<<(ostream& os,
                    const mcdane::botlib::TileTemplate& t)
{
    using namespace mcdane::botlib;

    os << "TileTemplate(" << &t
       << ", hp=" << t.hp()
       << ", Base=" << static_cast<const CompositeObjectTemplate&>(t)
       << ")";

    return os;
}

} // end of namespace std


