#include <botlib_ai_robot_template.h>
#include <botlib_ai_robot_template_parser.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

AIRobotTemplateParser::AIRobotTemplateParser(
            const MissileTemplateLib& missileTemplateLib,
            const ComponentTemplateLib& componentTemplateLib)
    : RobotTemplateParser(missileTemplateLib,
                          componentTemplateLib)
{
}

AIRobotTemplate* AIRobotTemplateParser::operator()(const rapidjson::Value& v)
{
    RobotTemplateParser::load(v);

    return new AIRobotTemplate(hp_,
                               armor_,
                               speed_,
                               energy_,
                               rechargeRate_,
                               collideBreath_,
                               missileTemplate_,
                               fireIntervalMS_,
                               std::move(components_),
                               std::move(firePoints_),
                               std::move(fireDirections_));
}

} // end of namespace botlib
} // end of namespace mcdane

