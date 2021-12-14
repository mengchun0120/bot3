#include <botlib_missile.h>

namespace mcdane {
namespace botlib {

void Missile::init(const MissileTemplate* t,
                   float x,
                   float y,
                   float directionX,
                   float directionY)
{
    CompositeObject::init(t, x, y, directionX, directionY);
    resetSpeed();
}

void Missile::init(const MissileTemplate* t,
                   const commonlib::Vector2& pos,
                   const commonlib::Vector2& direction)
{
    init(t, pos[0], pos[1], direction[0], direction[1]);
}

void Missile::update(GameMap& map,
                     float timeDelta) override
{
}

void Missile::setDirection(float directionX,
                           float directionY) override
{
    CompositeObject::setDirection(directionX, directionY);
    resetSpeed();
}

void Missile::resetSpeed()
{
    speedX_ = speed() * directionX_;
    speedY_ = speed() * directionY_;
}

} // end of namespace botlib
} // end of namespace mcdane

