#include <botlib_ai_robot.h>

namespace mcdane {
namespace botlib {

void AIRobot::init(const AIRobotTemplate* t,
                   const commonlib::Vector2& pos1,
                   const commonlib::Vector2& direction1)
{
    Robot::init(t, Side::AI, pos1, direction1);
}

} // end of namespace botlib
} // end of namespace mcdane

