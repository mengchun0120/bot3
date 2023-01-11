#include <botlib_shoot_missile_skill_template.h>
#include <botlib_shoot_missile_skill.h>
#include <botlib_skill_factory.h>

namespace mcdane {
namespace botlib {

Skill* SkillFactory::create(const SkillTemplate* t, Robot* robot)
{
    switch(t->type())
    {
        case SkillType::SHOOT_MISSILE:
        {
            ShootMissileSkill *skill = new ShootMissileSkill();
            skill->init(static_cast<const ShootMissileSkillTemplate*>(t), robot);
            return skill;
        }
        default:
        {
            break;
        }
    }

    return nullptr;
}

} // end of namespace botlib
} // end of namespace mcdane
