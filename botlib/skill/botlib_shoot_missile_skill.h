#ifndef INCLUDED_BOTLIB_SHOOT_MISSILE_SKILL_H
#define INCLUDED_BOTLIB_SHOOT_MISSILE_SKILL_H

#include <botlib_shoot_missile_skill_template.h>
#include <botlib_skill_with_cost.h>

namespace mcdane {
namespace botlib {

class ShootMissileSkill: public SkillWithCost {
public:
    ShootMissileSkill() = default;

    ShootMissileSkill(const ShootMissileSkillTemplate *t,
                      Robot *robot,
                      bool enabled1=false);

    ~ShootMissileSkill() override = default;

    void init(const ShootMissileSkillTemplate *t,
              Robot *robot,
              bool enabled1=false);

    inline const ShootMissileSkillTemplate *getTemplate() const;

protected:
    bool apply(UpdateContext &cxt) override;
};

const ShootMissileSkillTemplate *ShootMissileSkill::getTemplate() const
{
    return static_cast<const ShootMissileSkillTemplate*>(t_);
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
