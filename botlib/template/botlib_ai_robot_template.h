#ifndef INCLUDED_BOTLIB_AI_ROBOT_TEMPLATE_H
#define INCLUDED_BOTLIB_AI_ROBOT_TEMPLATE_H

#include <botlib_robot_template.h>

namespace mcdane {
namespace botlib {

class AIRobotTemplate: public RobotTemplate {
public:
    AIRobotTemplate() = default;

    ~AIRobotTemplate() = default;

    void init(const rapidjson::Value& v,
              const MissileTemplateLib& missileTemplateLib,
              const ComponentTemplateLib& componentTemplateLib);
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

