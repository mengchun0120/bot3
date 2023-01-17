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
    Skill::init(t, robot, true);
    timeSinceLastShoot_ = 0.0f;
}

void ShootMissileSkill::update(UpdateContext& cxt)
{
    timeSinceLastShoot_ += cxt.timeDelta();

    if (!available())
    {
        return;
    }

    GameMap& map = *(cxt.map());
    const MissileTemplate* missileTemplate = robot_->getTemplate()->missileTemplate();
    const std::vector<Component>& components = robot_->components();

    for (auto it = components.begin(); it != components.end(); ++it)
    {
        if (it->getTemplate()->type() != ComponentType::GUN)
        {
            continue;
        }

        Missile* missile = new Missile();
        missile->init(missileTemplate, robot_->side(),
                      it->firePos(), it->direction(),
                      robot_->damageFactor());
        map.addObj(missile);
    }

    timeSinceLastShoot_ = 0.0f;
    if (!getTemplate()->keepAlive())
    {
        setEnabled(false);
    }

    Skill::update(cxt);
}

} // end of namespace botlib
} // end of namespace mcdane
