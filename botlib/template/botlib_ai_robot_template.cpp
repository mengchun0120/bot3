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

} // end of namespace botlib
} // end of namespace mcdane

