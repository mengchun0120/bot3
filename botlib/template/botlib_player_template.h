#ifndef INCLUDED_BOTLIB_PLAYER_TEMPLATE_H
#define INCLUDED_BOTLIB_PLAYER_TEMPLATE_H

#include <botlib_robot_template.h>

namespace mcdane {
namespace botlib {

class PlayerTemplate: public RobotTemplate {
public:
    PlayerTemplate() = default;

    PlayerTemplate(float hp1,
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

