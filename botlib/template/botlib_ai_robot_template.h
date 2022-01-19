#ifndef INCLUDED_BOTLIB_AI_ROBOT_TEMPLATE_H
#define INCLUDED_BOTLIB_AI_ROBOT_TEMPLATE_H

#include <botlib_robot_template.h>

namespace mcdane {
namespace botlib {

class AIRobotTemplate: public RobotTemplate {
public:
    AIRobotTemplate() = default;

    AIRobotTemplate(float hp1,
                    float armor1,
                    float speed1,
                    float energy1,
                    float rechargeRate1,
                    float collideBreath1,
                    const MissileTemplate* missileTemplate1,
                    float fireIntervalMS1,
                    std::vector<Component>&& components,
                    std::vector<commonlib::Vector2>&& firePoints,
                    std::vector<commonlib::Vector2>&& fireDirections);

    ~AIRobotTemplate() = default;

    void init(float hp1,
              float armor1,
              float speed1,
              float energy1,
              float rechargeRate1,
              float collideBreath1,
              const MissileTemplate* missileTemplate1,
              float fireIntervalMS1,
              std::vector<Component>&& components,
              std::vector<commonlib::Vector2>&& firePoints,
              std::vector<commonlib::Vector2>&& fireDirections);

    std::string toString() const override;

    rapidjson::Value toJson(
                rapidjson::Document::AllocatorType& allocator) const override;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif
