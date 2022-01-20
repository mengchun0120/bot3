#include <sstream>
#include <commonlib_log.h>
#include <botlib_ai_robot.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void AIRobot::init(const AIRobotTemplate* t,
                   const Vector2& pos1,
                   const Vector2& direction1)
{
    Robot::init(t, Side::AI, pos1, direction1);
}

std::string AIRobot::toString() const
{
    std::ostringstream oss;

    oss << "AIRobot(" << this
        << ", Base=" << Robot::toString()
        << ")";

    return oss.str();
}

rapidjson::Value AIRobot::toJson(
                rapidjson::Document::AllocatorType& allocator) const
{
    using namespace rapidjson;

    Value v(kObjectType);

    v.AddMember("class", "AIRobot", allocator);
    v.AddMember("base", Robot::toJson(allocator), allocator);

    return v;
}

} // end of namespace botlib
} // end of namespace mcdane

