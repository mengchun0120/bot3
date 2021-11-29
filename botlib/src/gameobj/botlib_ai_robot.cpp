#include <botlib_ai_robot.h>

namespace mcdane {
namespace botlib {

void AIRobot::init(const AIRobotTemplate* t,
                   float x,
                   float y,
                   float directionX,
                   float directionY)
{
    Robot::init(t, x, y, directionX, directionY);
}

void AIRobot::init(const AIRobotTemplate* t,
                   const commonlib::Vector2& pos,
                   const commonlib::Vector2& direction)
{
    Robot::init(t, pos, direction);
}

} // end of namespace botlib
} // end of namespace mcdane

