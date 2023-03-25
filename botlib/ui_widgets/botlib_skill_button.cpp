#include <commonlib_log.h>
#include <botlib_progress_pie_template.h>
#include <botlib_skill_button.h>

namespace mcdane {
namespace botlib {

void SkillButton::init(float x,
                       float y,
                       const ProgressPieTemplate *t,
                       float coolDown,
                       Action action)
{
    Widget::init(x, y, true, true, true);
    pie_.init(t);
    action_ = action;
    coolDown_ = coolDown;
    cooling_ = false;
    duration_ = 0.0f;
    radiusSquare_ = t->radius() * t->radius();
}

void SkillButton::present() const
{
    pie_.present(pos_);
}

void SkillButton::update(float timeDelta)
{
    if (!cooling_)
    {
        return;
    }

    duration_ += timeDelta;
    pie_.setFinishedRatio(duration_ / coolDown_);

    if (duration_ >= coolDown_)
    {
        cooling_ = false;
    }
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
    if (enabled())
    {
        action_();
        cooling_ = true;
        duration_ = 0.0f;
    }
}

void SkillButton::reset()
{
    pie_.setFinishedRatio(1.0f);
    cooling_ = false;
}

} // end of namespace botlib
} // end of namespace mcdane
