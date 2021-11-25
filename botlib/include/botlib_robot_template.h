#ifndef INCLUDED_BOTLIB_ROBOT_TEMPLATE_H
#define INCLUDED_BOTLIB_ROBOT_TEMPLATE_H

#include <botlib_composite_object_template.h>

namespace mcdane {
namespace botlib {

class RobotTemplate: public CompositeObjectTemplate {
public:
    RobotTemplate(float hp,
                  float armor,
                  float speed,
                  float energy,
                  float rechargeRate,
                  float collideBreath,
                  std::vector<Component>&& components,
                  std::vector<commonlib::Vector2>&& firePoints,
                  std::vector<commonlib::Vector2>&& fireDirections);

    ~RobotTemplate() override = default;

    inline float hp() const;

    inline float armor() const;

    inline float speed() const;

    inline float energy() const;

    inline float rechargeRate() const;

    inline unsigned int numFirePoints() const;

    inline const commonlib::Vector2& firePoint(unsigned int i) const;

    inline const commonlib::Vector2& fireDirection(unsigned int i) const;

protected:
    float hp_;
    float armor_;
    float speed_;
    float energy_;
    float rechargeRate_;
    std::vector<commonlib::Vector2> firePoints_;
    std::vector<commonlib::Vector2> fireDirections_;
};

float RobotTemplate::hp() const
{
    return hp_;
}

float RobotTemplate::armor() const
{
    return armor_;
}

float RobotTemplate::speed() const
{
    return speed_;
}

float RobotTemplate::energy() const
{
    return energy_;
}

float RobotTemplate::rechargeRate() const
{
    return rechargeRate_;
}

unsigned int RobotTemplate::numFirePoints() const
{
    return firePoints_.size();
}

const commonlib::Vector2& RobotTemplate::firePoint(unsigned int i) const
{
    return firePoints_[i];
}

const commonlib::Vector2& RobotTemplate::fireDirection(unsigned int i) const
{
    return fireDirections_[i];
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

