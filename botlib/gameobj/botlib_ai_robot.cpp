#include <commonlib_log.h>
#include <botlib_ai.h>
#include <botlib_update_context.h>
#include <botlib_ai_robot.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

AIRobot::AIRobot()
    : ai_(nullptr)
{
}

AIRobot::~AIRobot()
{
    delete ai_;
}

void AIRobot::init(const AIRobotTemplate* t,
                   const Vector2& pos1,
                   const Vector2& direction1)
{
    ai_ = AI::create(t->aiAlgorithm(), t->aiName());

    Robot::init(t, Side::AI, pos1, direction1);
}

void AIRobot::update(UpdateContext& cxt)
{
    if (ai_ && state() == GameObjectState::ALIVE)
    {
        ai_->apply(*this, *(cxt.map()), cxt.timeDelta());
    }

    Robot::update(cxt);
}

} // end of namespace botlib
} // end of namespace mcdane

