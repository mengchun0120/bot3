#include <commonlib_exception.h>
#include <commonlib_log.h>
#include <botlib_context.h>
#include <botlib_chase_shoot_ai.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void AI::init(AIRobot *robot)
{
    robot_ = robot;
}

} // end of namespace botlib
} // end of namespace mcdane

