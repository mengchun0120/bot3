#ifndef INCLUDED_BOTLIB_ROBOT_TEMPLATE_H
#define INCLUDED_BOTLIB_ROBOT_TEMPLATE_H

#include <botlib_composite_object_template.h>

namespace mcdane {
namespace botlib {

class RobotTemplate: public CompositeObjectTemplate {
public:
    RobotTemplate(float hp,
                  float armor,
                  float energy,
                  float rechargeRate,
                  float collideBreath,
                  std::vector<Component>&& components,
                  std::vector<commonlib::Vector2>&& firePoints);

    ~RobotTemplate() override = default;

    inline float hp() const;

    inline float armor() const;

    inline float energy() const;

    inline float rechargeRate() const;

protected:
    float hp_;
    float armor_;
    float energy_;
    float rechargeRate_;
    std::vector<commonlib::Vector2> firePoints_;
};

float RobotTemplate::hp() const
{
    return hp_;
}

float RobotTemplate::armor() const
{
    return armor_;
}

float RobotTemplate::energy() const
{
    return energy_;
}

float RobotTemplate::rechargeRate() const
{
    return rechargeRate_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

