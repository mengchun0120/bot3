#include <commonlib_math_utils.h>
#include <botlib_robot.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

Robot::Robot()
    : hp_(0.0f)
    , energy_(0.0f)
{
}

void Robot::init(const RobotTemplate* t,
                 const commonlib::Vector2& pos,
                 const commonlib::Vector2& direction)
{
    CompositeObject::init(t, pos, direction);
    initFirePointsAndDirections();
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

} // end of namespace botlib
} // end of namespace mcdane

