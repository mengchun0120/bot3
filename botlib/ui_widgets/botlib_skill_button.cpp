#include <commonlib_log.h>
#include <botlib_progress_pie_template.h>
#include <botlib_skill_with_cost.h>
#include <botlib_skill_button.h>

namespace mcdane {
namespace botlib {

void SkillButton::init(float x,
                       float y,
                       const ProgressPieTemplate *t,
                       Action action,
                       SkillWithCost *skill)
{
    Widget::init(x, y, true, true);
    skill_ = skill;
    pie_.init(t, &pos_);
    action_ = action;
    radiusSquare_ = t->radius() * t->radius();
    enabled_ = true;
}

void SkillButton::present() const
{
    if (!visible_)
    {
        return;
    }

    pie_.present(enabled_ ? 0 : 1);
}

void SkillButton::update(float timeDelta)
{
    if (skill_)
    {
        pie_.setFinishedRatio(skill_->ratio());
        enabled_ = skill_->available();
    }
}

bool SkillButton::containPos(float x, float y) const
{
    float dx = x - pos_[0];
    float dy = y - pos_[1];
    return dx*dx + dy*dy <= radiusSquare_;
}

void SkillButton::onPointerDown(float x, float y)
{
    if (enabled_)
    {
        action_(*this);
    }
}

void SkillButton::setPos(float x, float y)
{
    Widget::setPos(x, y);
    pie_.setPos(pos_);
}

void SkillButton::shiftPos(float dx, float dy)
{
    Widget::shiftPos(dx, dy);
    pie_.setPos(pos_);
}

void SkillButton::setEnabled(bool b)
{
    enabled_ = b;
}

void SkillButton::setRatio(float ratio)
{
    pie_.setFinishedRatio(ratio);
}

} // end of namespace botlib
} // end of namespace mcdane
