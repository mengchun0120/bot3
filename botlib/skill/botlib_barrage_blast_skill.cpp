#include <commonlib_log.h>
#include <botlib_update_context.h>
#include <botlib_game_map.h>
#include <botlib_robot.h>
#include <botlib_barrage_blast_skill.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

BarrageBlastSkill::BarrageBlastSkill()
    : shootTimes_(0)
    , timeSinceLastShoot_(0.0f)
{
}

BarrageBlastSkill::BarrageBlastSkill(const BarrageBlastSkillTemplate* t,
                                     Robot* robot,
                                     bool enabled1)
{
    init(t, robot, enabled1);
}

void BarrageBlastSkill::init(const BarrageBlastSkillTemplate* t,
                             Robot* robot,
                             bool enabled1)
{
    SkillWithCost::init(t, robot, enabled1);

    shootTimes_ = 0;
    timeSinceLastShoot_ = getTemplate()->shootInterval();
}

bool BarrageBlastSkill::apply(UpdateContext& cxt)
{
    timeSinceLastShoot_ += cxt.timeDelta();

    if (timeSinceLastShoot_ < getTemplate()->shootInterval())
    {
        return false;
    }

    blast(cxt);
    timeSinceLastShoot_ = 0.0f;
    ++shootTimes_;

    if (shootTimes_ >= getTemplate()->maxShootTimes())
    {
        setInProcess(false);
        shootTimes_ = 0;
        timeSinceLastShoot_ = getTemplate()->shootInterval();
    }
    else if (shootTimes_ == 1)
    {
        setInProcess(true);
    }

    return shootTimes_ == 1;
}

void BarrageBlastSkill::blast(UpdateContext& cxt)
{
    GameMap& map = *(cxt.map());
    auto& firePoints = getTemplate()->firePoints();
    auto& fireDirections = getTemplate()->fireDirections();
    const MissileTemplate* missileTemplate = robot_->getTemplate()->missileTemplate();
    int sz = static_cast<int>(firePoints.size());

    for (int i = 0; i < sz; ++i)
    {
        Vector2 pos = robot_->pos() + firePoints[i];
        Missile* missile =
            cxt.factory().createMissile(missileTemplate, robot_->side(),
                                        pos, fireDirections[i]);
        map.addObj(missile);
    }
}

} // end of namespace botlib
} // end of namespace mcdane
