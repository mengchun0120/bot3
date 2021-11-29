#ifndef INCLUDED_BOTLIB_AI_ROBOT_TEMPLATE_H
#define INCLUDED_BOTLIB_AI_ROBOT_TEMPLATE_H

#include <botlib_robot_template.h>

namespace mcdane {
namespace botlib {

class AIRobotTemplate: public RobotTemplate {
public:
    AIRobotTemplate(float hp,
                    float armor,
                    float speed,
                    float energy,
                    float rechargeRate,
                    float collideBreath,
                    std::vector<Component>&& components,
                    std::vector<commonlib::Vector2>&& firePoints,
                    std::vector<commonlib::Vector2>&& fireDirections);

    ~AIRobotTemplate() = default;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

