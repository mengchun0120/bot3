#ifndef INCLUDED_BOTLIB_AI_ROBOT_TEMPLATE_H
#define INCLUDED_BOTLIB_AI_ROBOT_TEMPLATE_H

#include <botlib_robot_template.h>

namespace mcdane {
namespace botlib {

class AIRobotTemplate: public RobotTemplate {
public:
    AIRobotTemplate(float hp1,
                    float armor1,
                    float speed1,
                    float energy1,
                    float rechargeRate1,
                    float collideBreath1,
                    float fireIntervalMS1,
                    std::vector<Component>&& components,
                    std::vector<commonlib::Vector2>&& firePoints,
                    std::vector<commonlib::Vector2>&& fireDirections);

    ~AIRobotTemplate() = default;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

