#include <commonlib_exception.h>
#include <commonlib_string_utils.h>
#include <botlib_tile_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

TileTemplate::TileTemplate(float width,
                           float height,
                           float collideBreath,
                           float hp,
                           const commonlib::Texture* tex,
                           const Rectangle* r,
                           bool invincible)
    : GameObjectTemplate(GameObjectType::TILE, width, height, collideBreath,
                         invincible)
{
    init(hp, tex, r);
}

void TileTemplate::init(float hp,
                        const commonlib::Texture* tex,
                        const Rectangle* r)
{
    if (hp < 0.0f)
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid hp " + toString(hp));
    }

    if (!tex)
    {
        THROW_EXCEPT(InvalidArgumentException, "tex is null");
    }

    if (!r)
    {
        THROW_EXCEPT(InvalidArgumentException, "r is null");
    }

    hp_ = hp;
    texture_ = tex;
    rect_ = r;
}

} // end of namespace botlib
} // end of namespace mcdane

