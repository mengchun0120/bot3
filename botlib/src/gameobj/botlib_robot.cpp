#include <commonlib_log.h>
#include <commonlib_collide.h>
#include <botlib_game_map.h>
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
                 float x,
                 float y,
                 float directionX,
                 float directionY)
{
    CompositeObject::init(t, x, y, directionX, directionY);
    initFirePointsAndDirections();
    resetSpeed();
}

void Robot::init(const RobotTemplate* t,
                 const commonlib::Vector2& pos,
                 const commonlib::Vector2& direction)
{
    init(t, pos[0], pos[1], direction[0], direction[1]);
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
    float adjustedDeltaX, adjustedDeltaY;
    float left = x() - collideBreath();
    float right = x() + collideBreath();
    float bottom = y() - collideBreath();
    float top = y() + collideBreath();

    bool collideBoundary = checkRectCollideBoundary(adjustedDeltaX, adjustedDeltaY,
                                            left, right, bottom, top,
                                            0.0f, map.width(), 0.0f, map.height(),
                                            speedX_*timeDelta, speedY_*timeDelta);

    bool collideObjs = map.checkCollideNonPassthrough(
                                                adjustedDeltaX, adjustedDeltaY,
                                                this,
                                                adjustedDeltaX, adjustedDeltaY);

    if (collideBoundary || collideObjs)
    {
        setMovingEnabled(false);
    }

    shiftPos(adjustedDeltaX, adjustedDeltaY);
    map.repositionObj(this);
}

} // end of namespace botlib
} // end of namespace mcdane

