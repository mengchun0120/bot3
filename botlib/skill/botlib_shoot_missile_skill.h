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

    void update(UpdateContext& cxt) override;

protected:
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
           t_->coolDown() <= timeSinceLastShoot_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
