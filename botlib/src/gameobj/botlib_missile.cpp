#include <commonlib_collide.h>
#include <botlib_game_map.h>
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

    Vector2 delta{speedX_ * timeDelta, speedY_ * timeDelta};

    bool collideBoundary = checkRectCollideBoundary(delta, collideRegion(),
                                                    map.boundary(), delta);

    shiftPos(delta);
    map.repositionObj(this);

    bool collideObjs = checkCollideObjs(map);

    if (collideBoundary || collideObjs)
    {
        setAlive(false);
    }
}

void Missile::setDirection(const commonlib::Vector2& direction1)
{
    CompositeObject::setDirection(direction1);
    resetSpeed();
}

void Missile::resetSpeed()
{
    speedX_ = speed() * direction_[0];
    speedY_ = speed() * direction_[1];
}

bool Missile::checkCollideObjs(GameMap& map)
{
    using namespace std::placeholders;

    static MissileHitChecker checker;
    static GameMap::Accessor accessor = std::bind(&MissileHitChecker::run,
                                                  &checker, _1);

    Region<int> area = map.getCollideArea(collideRegion());

    checker.reset(this);
    map.accessRegion(area, accessor);

    return checker.collide();
}

} // end of namespace botlib
} // end of namespace mcdane

