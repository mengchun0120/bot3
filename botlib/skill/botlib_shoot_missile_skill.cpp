#include <commonlib_log.h>
#include <botlib_update_context.h>
#include <botlib_component_template.h>
#include <botlib_game_map.h>
#include <botlib_missile.h>
#include <botlib_skill_template.h>
#include <botlib_shoot_missile_skill.h>

namespace mcdane {
namespace botlib {

ShootMissileSkill::ShootMissileSkill()
    : Skill()
    , timeSinceLastShoot_(0.0f)
{
}

ShootMissileSkill::ShootMissileSkill(const ShootMissileSkillTemplate* t,
                                     Robot* robot)
{
    init(t, robot);
}

void ShootMissileSkill::init(const ShootMissileSkillTemplate* t,
                             Robot* robot)
{
    Skill::init(t, robot);
    timeSinceLastShoot_ = 0.0f;
}

void ShootMissileSkill::update(UpdateContext& cxt)
{
    timeSinceLastShoot_ += cxt.timeDelta();

    if (!available())
    {
        return;
    }

    robot_->shoot(cxt);
    robot_->addEnergy(-t_->energyCost());
    timeSinceLastShoot_ = 0.0f;

    if (!getTemplate()->keepAlive())
    {
        setEnabled(false);
    }
}

} // end of namespace botlib
} // end of namespace mcdane
