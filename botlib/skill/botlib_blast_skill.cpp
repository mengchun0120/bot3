#include <commonlib_log.h>
#include <botlib_update_context.h>
#include <botlib_game_map.h>
#include <botlib_missile.h>
#include <botlib_robot.h>
#include <botlib_blast_skill.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

BlastSkill::BlastSkill()
    : Skill()
    , timeSinceLastBlast_(0.0f)
{
}

BlastSkill::BlastSkill(const BlastSkillTemplate *t, Robot* robot)
{
    init(t, robot);
}

void BlastSkill::init(const BlastSkillTemplate *t, Robot* robot)
{
    Skill::init(t, robot);
    timeSinceLastBlast_ = t->coolDown();
}

void BlastSkill::update(UpdateContext& cxt)
{
    timeSinceLastBlast_ += cxt.timeDelta();

    if (!available())
    {
        if (!getTemplate()->keepAlive())
        {
            setEnabled(false);
        }
        return;
    }

    GameMap& map = *(cxt.map());
    auto& firePoints = getTemplate()->firePoints();
    auto& fireDirections = getTemplate()->fireDirections();
    const MissileTemplate* missileTemplate = getTemplate()->missileTemplate();
    int sz = static_cast<int>(firePoints.size());

    for (int i = 0; i < sz; ++i)
    {
        Vector2 pos = robot_->pos() + firePoints[i];
        Missile* missile = new Missile();
        missile->init(missileTemplate, robot_->side(), pos, fireDirections[i]);
        map.addObj(missile);
    }

    timeSinceLastBlast_ = 0.0f;
    robot_->addEnergy(-t_->energyCost());

    if (!getTemplate()->keepAlive())
    {
        setEnabled(false);
    }
}

} // end of namespace botlib
} // end of namespace mcdane
