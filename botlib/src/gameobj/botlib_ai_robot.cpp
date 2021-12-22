#include <botlib_ai_robot.h>

namespace mcdane {
namespace botlib {

void AIRobot::init(const AIRobotTemplate* t,
                   const commonlib::Vector2& pos,
                   const commonlib::Vector2& direction)
{
    Robot::init(t, Side::AI, pos, direction);
}

} // end of namespace botlib
} // end of namespace mcdane

