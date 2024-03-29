#include <commonlib_log.h>
#include <botlib_ai.h>
#include <botlib_ai_factory.h>
#include <botlib_update_context.h>
#include <botlib_ai_robot.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

AIRobot::AIRobot()
    : Robot()
    , ai_(nullptr)
{
}

AIRobot::AIRobot(const AIRobotTemplate *t,
                 const commonlib::Vector2 &pos1,
                 const commonlib::Vector2 &direction1)
{
    init(t, pos1, direction1);
}

AIRobot::~AIRobot()
{
    delete ai_;
}

void AIRobot::init(const AIRobotTemplate *t,
                   const Vector2 &pos1,
                   const Vector2 &direction1)
{
    Robot::init(t, Side::AI, pos1, direction1);
    ai_ = AIFactory::create(this, t->aiAlgorithm(), t->aiName());
}

void AIRobot::update(UpdateContext &cxt)
{
    if (!cxt.exerciseMode() && ai_ && state() == GameObjectState::ALIVE)
    {
        ai_->apply(*(cxt.map()), cxt.timeDelta());
    }

    Robot::update(cxt);
}

void AIRobot::toJson(rapidjson::Value &v,
                     rapidjson::Document::AllocatorType &allocator)
{
    Robot::toJson(v, allocator);
    v.AddMember("type", jsonVal("robot", allocator), allocator);
}

} // end of namespace botlib
} // end of namespace mcdane

