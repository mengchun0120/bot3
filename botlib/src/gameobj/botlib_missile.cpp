#include <commonlib_collide.h>
#include <botlib_game_map.h>
#include <botlib_missile_hit_checker.h>
#include <botlib_missile.h>

using namespace mcdane::commonlib;

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
    damage_ = t->damage();
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
    if (!alive())
    {
        return;
    }

    float deltaX = speedX_ * timeDelta;
    float deltaY = speedY_ * timeDelta;

    bool collideBoundary = checkRectCollideBoundary(
                                        deltaX, deltaY,
                                        collideLeft(), collideRight(),
                                        collideBottom(), collideTop(),
                                        0.0f, map.width(), 0.0f, map.height(),
                                        deltaX, deltaY);

    shiftPos(deltaX, deltaY);
    map.repositionObj(this);

    bool collideObjs = checkCollideObjs(map);

    if (collideBoundary || collideObjs)
    {
        setAlive(false);
    }
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

bool Missile::checkCollideObjs(GameMap& map)
{
    using namespace std::placeholders;

    static MissileHitChecker checker;
    static GameMap::Accessor accessor = std::bind(&MissileHitChecker::run,
                                                  &checker, _1);

    int startRow, endRow, startCol, endCol;
    map.getCollideArea(startRow, endRow, startCol, endCol,
                       collideLeft(), collideRight(),
                       collideBottom(), collideTop());

    checker.reset(this);
    map.accessRegion(startRow, endRow, startCol, endCol, accessor);

    return checker.collide();
}

} // end of namespace botlib
} // end of namespace mcdane

