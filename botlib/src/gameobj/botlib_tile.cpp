#include <commonlib_exception.h>
#include <commonlib_math_utils.h>
#include <botlib_graphics.h>
#include <botlib_tile.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void Tile::init(const TileTemplate* t,
                float x,
                float y,
                float directionX,
                float directionY)
{
    CompositeObject::init(t, x, y, directionX, directionY);
    hp_ = t->hp();
}

void Tile::init(const TileTemplate* t,
                const commonlib::Vector2& pos,
                const commonlib::Vector2& direction)
{
    init(t, pos[0], pos[1], direction[0], direction[1]);
}

void Tile::addHP(float delta)
{
    const TileTemplate* t = getTemplate();

    if (t->invincible())
    {
        return;
    }

    hp_ = clamp(hp_+delta, 0.0f, t->hp());
    if (hp_ <= 0.0f)
    {
        alive_ = false;
    }
}

} // end of namespace botlib
} // end of namespace mcdane

