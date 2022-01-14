#ifndef INCLUDED_BOTLIB_ROBOT_TEMPLATE_H
#define INCLUDED_BOTLIB_ROBOT_TEMPLATE_H

#include <botlib_missile_template.h>
#include <botlib_composite_object_template.h>

namespace mcdane {
namespace botlib {

class RobotTemplate: public CompositeObjectTemplate {
public:
    RobotTemplate() = default;

    RobotTemplate(float hp1,
                  float armor1,
                  float speed1,
                  float energy1,
                  float rechargeRate1,
                  float collideBreath1,
                  const MissileTemplate* missileTemplate1,
                  float fireIntervalMS1,
                  std::vector<Component>&& components,
                  std::vector<commonlib::Vector2>&& firePoints1,
                  std::vector<commonlib::Vector2>&& fireDirections1);

    ~RobotTemplate() override = default;

    void init(float hp1,
              float armor1,
              float speed1,
              float energy1,
              float rechargeRate1,
              float collideBreath1,
              const MissileTemplate* missileTemplate1,
              float fireIntervalMS1,
              std::vector<Component>&& components,
              std::vector<commonlib::Vector2>&& firePoints1,
              std::vector<commonlib::Vector2>&& fireDirections1);

    inline float hp() const;

    inline float armor() const;

    inline float speed() const;

    inline float energy() const;

    inline float rechargeRate() const;

    inline const MissileTemplate* missileTemplate() const;

    inline float fireIntervalMS() const;

    inline unsigned int numFirePoints() const;

    inline const std::vector<commonlib::Vector2>& firePoints() const;

    inline const commonlib::Vector2& firePoint(unsigned int i) const;

    inline const std::vector<commonlib::Vector2>& fireDirections() const;

    inline const commonlib::Vector2& fireDirection(unsigned int i) const;

protected:
    float hp_;
    float armor_;
    float speed_;
    float energy_;
    float rechargeRate_;
    const MissileTemplate* missileTemplate_;
    float fireIntervalMS_;
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

const MissileTemplate* RobotTemplate::missileTemplate() const
{
    return missileTemplate_;
}

float RobotTemplate::fireIntervalMS() const
{
    return fireIntervalMS_;
}

unsigned int RobotTemplate::numFirePoints() const
{
    return firePoints_.size();
}

const std::vector<commonlib::Vector2>& RobotTemplate::firePoints() const
{
    return firePoints_;
}

const commonlib::Vector2& RobotTemplate::firePoint(unsigned int i) const
{
    return firePoints_[i];
}

const std::vector<commonlib::Vector2>& RobotTemplate::fireDirections() const
{
    return fireDirections_;
}

const commonlib::Vector2& RobotTemplate::fireDirection(unsigned int i) const
{
    return fireDirections_[i];
}

} // end of namespace botlib
} // end of namespace mcdane

namespace std {

ostream& operator<<(ostream& os,
                    const mcdane::botlib::RobotTemplate& t);

} // end of namespace std

#endif

