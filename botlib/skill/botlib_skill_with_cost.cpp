#include <algorithm>
#include <commonlib_log.h>
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
    , pie_(nullptr)
    , curIconIndex_(0)
{
}

SkillWithCost::SkillWithCost(const SkillTemplate* t,
                             Robot* robot,
                             bool enabled1)
{
    init(t, robot, enabled1);
}

SkillWithCost::~SkillWithCost()
{
    if (!pie_)
    {
        delete pie_;
    }
}

void SkillWithCost::init(const SkillTemplate* t,
                         Robot* robot,
                         bool enabled1)
{
    Skill::init(t, robot, enabled1);

    const SkillWithCostTemplate* t1 = getTemplate();

    coolDown_ = t1->coolDown();
    timeSinceLastCast_ = t1->coolDown();
    if (t1->pieTemplate())
    {
        pie_ = new ProgressPie(t1->pieTemplate());
        curIconIndex_ = 0;
    }
}

void SkillWithCost::update(UpdateContext& cxt)
{
    timeSinceLastCast_ += cxt.timeDelta();
    if (pie_)
    {
        updatePie();
    }

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
        robot_->addEnergy(getTemplate()->energyCost());
        timeSinceLastCast_ = 0.0f;
    }

    if (!inProcess() && !getTemplate()->keepAlive())
    {
        setEnabled(false);
    }
}

void SkillWithCost::setCoolDownFactor(float f)
{
    coolDown_ *= f;
}

void SkillWithCost::resetCoolDown()
{
    coolDown_ = getTemplate()->coolDown();
}

void SkillWithCost::updatePie()
{
    if (coolDown_ > 0.0f)
    {
        float finishedRatio = std::min(timeSinceLastCast_ / coolDown_, 1.0f);
        pie_->setFinishedRatio(finishedRatio);
    }

    curIconIndex_ = available() ? 0 : 1;
}

} // end of namespace botlib
} // end of namespace mcdane
