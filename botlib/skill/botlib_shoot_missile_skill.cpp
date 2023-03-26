#include <commonlib_log.h>
#include <botlib_update_context.h>
#include <botlib_shoot_missile_skill.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

ShootMissileSkill::ShootMissileSkill(const ShootMissileSkillTemplate *t,
                                     Robot *robot,
                                     bool enabled1,
                                     const Vector2 *buttonPos)
{
    init(t, robot, enabled1);
}

void ShootMissileSkill::init(const ShootMissileSkillTemplate *t,
                             Robot *robot,
                             bool enabled1,
                             const Vector2 *buttonPos)
{
    SkillWithCost::init(t, robot, enabled1, buttonPos);
}

bool ShootMissileSkill::apply(UpdateContext &cxt)
{
    robot_->shoot(cxt);
    return true;
}

} // end of namespace botlib
} // end of namespace mcdane
