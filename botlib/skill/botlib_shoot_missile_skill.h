#ifndef INCLUDED_BOTLIB_SHOOT_MISSILE_SKILL_H
#define INCLUDED_BOTLIB_SHOOT_MISSILE_SKILL_H

#include <botlib_robot.h>
#include <botlib_shoot_missile_skill_template.h>
#include <botlib_skill.h>

namespace mcdane {
namespace botlib {

class ShootMissileSkill: public Skill {
public:
    ShootMissileSkill();

    ShootMissileSkill(const ShootMissileSkillTemplate* t,
                      Robot* robot);

    ~ShootMissileSkill() = default;

    void init(const ShootMissileSkillTemplate* t,
              Robot* robot);

    inline const ShootMissileSkillTemplate* getTemplate() const;

    inline bool available() const;

    void setCoolDownFactor(float f);

    void update(UpdateContext& cxt) override;

protected:
    float coolDown_;
    float timeSinceLastShoot_;
};

const ShootMissileSkillTemplate* ShootMissileSkill::getTemplate() const
{
    return static_cast<const ShootMissileSkillTemplate*>(t_);
}

bool ShootMissileSkill::available() const
{
    return enabled() &&
           t_->energyCost() <= robot_->energy() &&
           coolDown_ <= timeSinceLastShoot_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
