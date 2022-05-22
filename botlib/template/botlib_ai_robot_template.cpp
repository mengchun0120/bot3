#include <utility>
#include <sstream>
#include <botlib_ai_robot_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void AIRobotTemplate::init(const rapidjson::Value& v,
                           const MissileTemplateLib& missileTemplateLib,
                           const ComponentTemplateLib& componentTemplateLib)
{
    RobotTemplate::init(v, missileTemplateLib, componentTemplateLib);
}

rapidjson::Value AIRobotTemplate::toJson(
                rapidjson::Document::AllocatorType& allocator) const
{
    using namespace rapidjson;

    Value v(kObjectType);

    v.AddMember("class", "AIRobotTemplate", allocator);
    v.AddMember("base", RobotTemplate::toJson(allocator), allocator);

    return v;
}

} // end of namespace botlib
} // end of namespace mcdane

