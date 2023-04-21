#include <commonlib_log.h>
#include <botlib_update_context.h>
#include <botlib_robot.h>
#include <botlib_barrage_skill.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

BarrageSkill::BarrageSkill()
    : SkillWithCost()
    , shootTimes_(0)
    , timeSinceLastShoot_(0.0f)
{
}

BarrageSkill::BarrageSkill(const BarrageSkillTemplate *t,
                           Robot *robot,
                           bool enabled1)
{
    init(t, robot, enabled1);
}

void BarrageSkill::init(const BarrageSkillTemplate *t,
                        Robot *robot,
                        bool enabled1)
{
    SkillWithCost::init(t, robot, enabled1);

    shootTimes_ = 0;
    timeSinceLastShoot_ = getTemplate()->shootInterval();
}

bool BarrageSkill::apply(UpdateContext &cxt)
{
    timeSinceLastShoot_ += cxt.timeDelta();

    if (timeSinceLastShoot_ < getTemplate()->shootInterval())
    {
        return false;
    }

    robot_->shoot(cxt);
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

} // end of namespace botlib
} // end of namespace mcdane
