#include <sstream>
#include <commonlib_log.h>
#include <commonlib_collide.h>
#include <botlib_game_map.h>
#include <botlib_particle_effect.h>
#include <botlib_missile_hit_checker.h>
#include <botlib_missile.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void Missile::init(const MissileTemplate* t,
                   Side side,
                   const commonlib::Vector2& pos1,
                   const commonlib::Vector2& direction1)
{
    CompositeObject::init(t, pos1, direction1);
    side_ = side;
    damage_ = t->damage();
    resetSpeed();
}

void Missile::update(GameMap& map,
                     float timeDelta)
{
    if (!alive())
    {
        return;
    }

    Vector2 delta = speed_ * timeDelta;

    bool collideBoundary = checkRectCollideBoundary(delta, collideRegion(),
                                                    map.boundary(), delta);

    shiftPos(delta);
    map.repositionObj(this);

    bool collideObjs = checkCollideObjs(map);

    if (collideBoundary || collideObjs)
    {
        explode(map);
    }

    GameObject::update(map, timeDelta);
}

void Missile::setDirection(const commonlib::Vector2& direction1)
{
    CompositeObject::setDirection(direction1);
    resetSpeed();
}

void Missile::explode(GameMap& map)
{
    MissileHitChecker checker(this, true);
    Region<int> area = map.getCollideArea(explodeRegion());
    map.accessRegion(area, checker, true);

    showExplodeEffect(map);
    setAlive(false);
}

void Missile::resetSpeed()
{
    speed_ = speedNorm() * direction_;
}

bool Missile::checkCollideObjs(GameMap& map)
{
    MissileHitChecker checker(this, false);
    Region<int> area = map.getCollideArea(collideRegion());
    map.accessRegion(area, checker, false);

    return checker.collide();
}

Region<float> Missile::explodeRegion()
{
    float breath = getTemplate()->explodeBreath();
    return Region<float>({x()-breath, x()+breath, y()-breath, y()+breath});
}

void Missile::showExplodeEffect(GameMap& map)
{
    ParticleEffect* explodeEffect = new ParticleEffect();
    explodeEffect->init(getTemplate()->explodeEffectTemplate(), pos_);
    map.addObj(explodeEffect);
}

std::string Missile::toString() const
{
    std::ostringstream oss;

    oss << "Missile(side=" << side_
        << ", speed=" << speed_
        << ", damage=" << damage_
        << ", Base=" << CompositeObject::toString()
        << ")";

    return oss.str();
}

} // end of namespace botlib
} // end of namespace mcdane

