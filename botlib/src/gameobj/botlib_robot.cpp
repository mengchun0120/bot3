#include <commonlib_log.h>
#include <commonlib_collide.h>
#include <botlib_game_map.h>
#include <botlib_nonpassthrough_collide_checker.h>
#include <botlib_robot.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

Robot::Robot()
    : hp_(0.0f)
    , energy_(0.0f)
    , movingEnabled_(false)
{
}

void Robot::init(const RobotTemplate* t,
                 Side side,
                 float x,
                 float y,
                 float directionX,
                 float directionY)
{
    CompositeObject::init(t, x, y, directionX, directionY);
    side_ = side;
    initFirePointsAndDirections();
    resetSpeed();
}

void Robot::init(const RobotTemplate* t,
                 Side side,
                 const commonlib::Vector2& pos,
                 const commonlib::Vector2& direction)
{
    init(t, side, pos[0], pos[1], direction[0], direction[1]);
}

void Robot::update(GameMap& map,
                   float timeDelta)
{
    if (movingEnabled_)
    {
        updatePos(map, timeDelta);
    }

    GameObject::update(map, timeDelta);
}

void Robot::shiftPos(float deltaX,
                     float deltaY)
{
    CompositeObject::shiftPos(deltaX, deltaY);
    resetFirePointsAndDirections();
}

void Robot::setDirection(float directionX,
                         float directionY)
{
    CompositeObject::setDirection(directionX, directionY);
    resetFirePointsAndDirections();
    resetSpeed();
}

void Robot::setMovingEnabled(bool b)
{
    movingEnabled_ = b;
}

void Robot::initFirePointsAndDirections()
{
    const RobotTemplate* t = getTemplate();

    firePoints_.resize(t->numFirePoints());
    fireDirections_.resize(t->numFirePoints());
    resetFirePointsAndDirections();
}

void Robot::shiftFirePoints(float deltaX,
                            float deltaY)
{
    for (std::size_t i = 0; i < firePoints_.size(); ++i)
    {
        firePoints_[i][0] += deltaX;
        firePoints_[i][1] += deltaY;
    }
}

void Robot::resetFirePointsAndDirections()
{
    const RobotTemplate* t = getTemplate();

    for (std::size_t i = 0; i < firePoints_.size(); ++i)
    {
        Vector2 p = t->firePoint(i);

        rotate(p[0], p[1], direction_[0], direction_[1]);
        firePoints_[i] = pos_ + p;

        Vector2 d = t->fireDirection(i);

        rotate(d[0], d[1], direction_[0], direction_[1]);
        fireDirections_[i] = d;
    }
}

void Robot::resetSpeed()
{
    speedX_ = speed() * direction_[0];
    speedY_ = speed() * direction_[1];
}

void Robot::updatePos(GameMap& map,
                      float timeDelta)
{
    float deltaX = speedX_ * timeDelta;
    float deltaY = speedY_ * timeDelta;

    bool collideBoundary = checkRectCollideBoundary(
                                        deltaX, deltaY,
                                        collideLeft(), collideRight(),
                                        collideBottom(), collideTop(),
                                        0.0f, map.width(), 0.0f, map.height(),
                                        deltaX, deltaY);

    bool collideObjs = checkNonpassthroughCollide(deltaX, deltaY, map,
                                                  deltaX, deltaY);
    if (collideBoundary || collideObjs)
    {
        setMovingEnabled(false);
    }

    shiftPos(deltaX, deltaY);
    map.repositionObj(this);
}

bool Robot::checkNonpassthroughCollide(float& adjustedDeltaX,
                                       float& adjustedDeltaY,
                                       GameMap& map,
                                       float deltaX,
                                       float deltaY)
{
    using namespace std::placeholders;

    static NonpassthroughCollideChecker checker;
    static GameMap::Accessor accessor = std::bind(
                                            &NonpassthroughCollideChecker::run,
                                            &checker, _1);

    int startRow, endRow, startCol, endCol;

    map.getCollideArea(startRow, endRow, startCol, endCol,
                       collideLeft(), collideRight(),
                       collideBottom(), collideTop(),
                       deltaX, deltaY);

    checker.reset(this, deltaX, deltaY);
    map.accessRegion(startRow, endRow, startCol, endCol, accessor);

    adjustedDeltaX = checker.adjustedDeltaX();
    adjustedDeltaY = checker.adjustedDeltaY();

    return checker.collide();
}

void Robot::addHP(float delta)
{
    const RobotTemplate* t = getTemplate();

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

