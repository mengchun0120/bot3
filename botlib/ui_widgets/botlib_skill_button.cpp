#include <commonlib_log.h>
#include <botlib_progress_pie_template.h>
#include <botlib_skill_button.h>

namespace mcdane {
namespace botlib {

void SkillButton::init(float x,
                       float y,
                       const ProgressPieTemplate *t,
                       Action action)
{
    Widget::init(x, y, true, true, true);
    pie_.init(t);
    action_ = action;
    radiusSquare_ = t->radius() * t->radius();
    enabled_ = true;
}

void SkillButton::present() const
{
    pie_.present(pos_, enabled_ ? 0 : 1);
}

bool SkillButton::containPos(float x, float y) const
{
    float dx = x - pos_[0];
    float dy = y - pos_[1];
    return dx*dx + dy*dy <= radiusSquare_;
}

void SkillButton::onLostFocus()
{
}

void SkillButton::onPointerOut()
{
}

void SkillButton::onPointerOver(float x, float y)
{
}

void SkillButton::onPointerDown(float x, float y)
{
    if (enabled_)
    {
        action_(*this);
    }
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
