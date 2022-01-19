#include <sstream>
#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_math_utils.h>
#include <botlib_graphics.h>
#include <botlib_tile.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void Tile::init(const TileTemplate* t,
                const commonlib::Vector2& pos1,
                const commonlib::Vector2& direction1)
{
    CompositeObject::init(t, pos1, direction1);
    setInvincible(t->invincible());
    hp_ = t->hp();
    hpIndicator_.reset(pos(), hpRatio());
}

void Tile::present() const
{
    CompositeObject::present();
    hpIndicator_.present();
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

    hpIndicator_.reset(pos(), hpRatio());
}

std::string Tile::toString() const
{
    std::ostringstream oss;

    oss << "Tile(" << this
        << ", hp=" << hp_
        << ", Base=" << CompositeObject::toString()
        << ")";

    return oss.str();
}

} // end of namespace botlib
} // end of namespace mcdane
