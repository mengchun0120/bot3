#include <commonlib_exception.h>
#include <commonlib_math_utils.h>
#include <botlib_graphics.h>
#include <botlib_tile.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void Tile::init(const TileTemplate* t,
                const commonlib::Vector2& pos,
                const commonlib::Vector2& direction)
{
    CompositeObject::init(t, pos, direction);
    setInvincible(t->invincible());
    hp_ = t->hp();
}

void Tile::addHP(float delta)
{
    const TileTemplate* t = getTemplate();

    if (invincible())
    {
        return;
    }

    hp_ = clamp(hp_+delta, 0.0f, t->hp());
    if (hp_ <= 0.0f)
    {
        setAlive(false);
    }
}

} // end of namespace botlib
} // end of namespace mcdane

