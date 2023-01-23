#include <botlib_move_skill.h>
#include <botlib_shoot_missile_skill.h>
#include <botlib_blast_skill.h>
#include <botlib_targeted_blast_skill.h>
#include <botlib_skill_factory.h>

namespace mcdane {
namespace botlib {

Skill* SkillFactory::create(const SkillTemplate* t, Robot* robot)
{
    switch(t->type())
    {
        case SkillType::MOVE:
        {
            return new MoveSkill(static_cast<const MoveSkillTemplate*>(t),
                                 robot);
        }
        case SkillType::SHOOT_MISSILE:
        {
            return new ShootMissileSkill(
                            static_cast<const ShootMissileSkillTemplate*>(t),
                            robot);
        }
        case SkillType::BLAST:
        {
            return new BlastSkill(static_cast<const BlastSkillTemplate*>(t),
                                  robot);
        }
        case SkillType::TARGETED_BLAST:
        {
            return new TargetedBlastSkill(
                            static_cast<const TargetedBlastSkillTemplate*>(t),
                            robot);
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
