#include <botlib_missile.h>

namespace mcdane {
namespace botlib {

void Missile::init(const MissileTemplate* t,
                   Side side,
                   float x,
                   float y,
                   float directionX,
                   float directionY)
{
    CompositeObject::init(t, x, y, directionX, directionY);
    side_ = side;
    resetSpeed();
}

void Missile::init(const MissileTemplate* t,
                   Side side,
                   const commonlib::Vector2& pos,
                   const commonlib::Vector2& direction)
{
    init(t, side, pos[0], pos[1], direction[0], direction[1]);
}

void Missile::update(GameMap& map,
                     float timeDelta)
{
}

void Missile::setDirection(float directionX,
                           float directionY)
{
    CompositeObject::setDirection(directionX, directionY);
    resetSpeed();
}

void Missile::resetSpeed()
{
    speedX_ = speed() * direction_[0];
    speedY_ = speed() * direction_[1];
}

} // end of namespace botlib
} // end of namespace mcdane

