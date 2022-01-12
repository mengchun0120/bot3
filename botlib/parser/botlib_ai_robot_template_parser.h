#ifndef INCLUDED_BOTLIB_AI_ROBOT_TEMPLATE_PARSER_H
#define INCLUDED_BOTLIB_AI_ROBOT_TEMPLATE_PARSER_H

#include <botlib_robot_template_parser.h>

namespace mcdane {
namespace botlib {

class AIRobotTemplate;

class AIRobotTemplateParser: public RobotTemplateParser {
public:
    AIRobotTemplateParser(
            const MissileTemplateLib& missileTemplateLib,
            const ComponentTemplateLib& componentTemplateLib);

    AIRobotTemplate* operator()(const rapidjson::Value& v);
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

