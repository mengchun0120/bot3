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
                   const Vector2& direction1,
                   GameObjItemDeleter itemDeleter)
{
    Robot::init(t, Side::AI, pos1, direction1, itemDeleter);
    ai_ = AI::create(t->aiAlgorithm(), t->aiName());
}

void AIRobot::update(UpdateContext& cxt)
{
    if (ai_ && state() == GameObjectState::ALIVE)
    {
        ai_->apply(*this, *(cxt.map()), cxt.timeDelta());
    }

    Robot::update(cxt);
}

void AIRobot::toJson(rapidjson::Value& v,
                     rapidjson::Document::AllocatorType& allocator)
{
    Robot::toJson(v, allocator);
    v.AddMember("type", jsonVal("robot", allocator), allocator);
}

} // end of namespace botlib
} // end of namespace mcdane

