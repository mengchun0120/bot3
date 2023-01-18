#include <botlib_move_skill.h>
#include <botlib_shoot_missile_skill.h>
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
        default:
        {
            break;
        }
    }

    return nullptr;
}

} // end of namespace botlib
} // end of namespace mcdane