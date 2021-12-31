#ifndef INCLUDED_BOTLIB_AI_ROBOT_TEMPLATE_PARSER_H
#define INCLUDED_BOTLIB_AI_ROBOT_TEMPLATE_PARSER_H

#include <botlib_robot_template_parser.h>
#include <botlib_ai_robot_template.h>

namespace mcdane {
namespace botlib {

class AIRobotTemplateParser: public RobotTemplateParser {
public:
    AIRobotTemplateParser(
            const commonlib::NamedMap<MissileTemplate>& missileTemplateLib,
            const commonlib::NamedMap<ComponentTemplate>& componentTemplateLib);

    AIRobotTemplate* operator()(const rapidjson::Value& v);
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

