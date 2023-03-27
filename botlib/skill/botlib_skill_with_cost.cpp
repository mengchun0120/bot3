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
    : button_(nullptr)
    , coolDown_(0.0f)
    , timeSinceLastCast_(0.0f)
{
}

SkillWithCost::SkillWithCost(const SkillTemplate *t,
                             Robot *robot,
                             bool enabled1,
                             const Vector2 *buttonPos)
{
    init(t, robot, enabled1, buttonPos);
}

SkillWithCost::~SkillWithCost()
{
    if (!button_)
    {
        delete button_;
    }
}

void SkillWithCost::init(const SkillTemplate *t,
                         Robot *robot,
                         bool enabled1,
                         const Vector2 *buttonPos)
{
    Skill::init(t, robot, enabled1);

    coolDown_ = getTemplate()->coolDown();
    timeSinceLastCast_ = coolDown_;

    if (getTemplate()->pieTemplate())
    {
        initButton(buttonPos);
    }
}

void SkillWithCost::update(UpdateContext &cxt)
{
    timeSinceLastCast_ += cxt.timeDelta();

    if (button_)
    {
        updateButton();
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
        robot_->addEnergy(-getTemplate()->energyCost());
        timeSinceLastCast_ = 0.0f;
        updateButton();
    }

    if (!inProcess() && !getTemplate()->keepAlive())
    {
        setEnabled(false);
    }
}

void SkillWithCost::setCoolDownFactor(float f)
{
    coolDown_ = getTemplate()->coolDown() * f;

    if (button_)
    {
        updateButton();
    }
}

void SkillWithCost::resetCoolDown()
{
    setCoolDownFactor(1.0f);
}

void SkillWithCost::initButton(const Vector2 *buttonPos)
{
    const SkillWithCostTemplate *t = getTemplate();
    auto action = [&](SkillButton &button)
    {
        setEnabled(true);
    };

    button_ = new SkillButton();

    if (buttonPos)
    {
        button_->init((*buttonPos)[0], (*buttonPos)[1],
                      t->pieTemplate(), action);
    }
    else
    {
        button_->init(0.0f, 0.0f, t->pieTemplate(), action);
    }
}

void SkillWithCost::updateButton()
{
    float ratio = coolDown_ > 0.0f ? timeSinceLastCast_ / coolDown_ : 1.0f;

    button_->setRatio(ratio);
    button_->setEnabled(available());
}

} // end of namespace botlib
} // end of namespace mcdane
