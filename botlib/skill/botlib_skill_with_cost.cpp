#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <botlib_update_context.h>
#include <botlib_progress_pie.h>
#include <botlib_skill_template.h>
#include <botlib_skill_with_cost.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

SkillWithCost::SkillWithCost()
    : coolDown_(0.0f)
    , timeSinceLastCast_(0.0f)
{
}

SkillWithCost::SkillWithCost(const SkillTemplate *t,
                             Robot *robot,
                             bool enabled1)
{
    init(t, robot, enabled1);
}

SkillWithCost::~SkillWithCost()
{
}

void SkillWithCost::init(const SkillTemplate *t,
                         Robot *robot,
                         bool enabled1)
{
    Skill::init(t, robot, enabled1);

    coolDown_ = getTemplate()->coolDown();
    timeSinceLastCast_ = coolDown_;
}

void SkillWithCost::update(UpdateContext &cxt)
{
    timeSinceLastCast_ += cxt.timeDelta();

    if (!inProcess() && (!enabled() || !available()))
    {
        if (!getTemplate()->keepAlive())
        {
            setEnabled(false);
        }

        return;
    }

    if (apply(cxt))
    {
        robot_->addEnergy(-getTemplate()->energyCost());
        timeSinceLastCast_ = 0.0f;
    }

    if (!inProcess() && !getTemplate()->keepAlive())
    {
        setEnabled(false);
    }
}

void SkillWithCost::setCoolDownFactor(float f)
{
    coolDown_ = getTemplate()->coolDown() * f;
}

void SkillWithCost::resetCoolDown()
{
    setCoolDownFactor(1.0f);
}

} // end of namespace botlib
} // end of namespace mcdane
