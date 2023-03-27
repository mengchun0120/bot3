#ifndef INCLUDED_BOTLIB_SKILL_WITH_COST_H
#define INCLUDED_BOTLIB_SKILL_WITH_COST_H

#include <botlib_robot.h>
#include <botlib_skill_button.h>
#include <botlib_skill_with_cost_template.h>
#include <botlib_skill.h>

namespace mcdane {
namespace botlib {

class SkillWithCost: public Skill {
public:
    SkillWithCost();

    SkillWithCost(const SkillTemplate *t,
                  Robot *robot,
                  bool enabled1=false,
                  const commonlib::Vector2 *buttonPos=nullptr);

    ~SkillWithCost() override;

    void init(const SkillTemplate *t,
              Robot *robot,
              bool enabled1=false,
              const commonlib::Vector2 *buttonPos=nullptr);

    inline const SkillWithCostTemplate *getTemplate() const;

    inline bool available() const;

    inline SkillButton *button();

    void update(UpdateContext &cxt) override;

    void setCoolDownFactor(float f);

    void resetCoolDown();

protected:
    void initButton(const commonlib::Vector2 *buttonPos);

    virtual bool apply(UpdateContext &cxt) = 0;

    void updateButton();

protected:
    SkillButton *button_;
    float coolDown_;
    float timeSinceLastCast_;
};

const SkillWithCostTemplate *SkillWithCost::getTemplate() const
{
    return static_cast<const SkillWithCostTemplate*>(t_);
}

bool SkillWithCost::available() const
{
    return robot_->energy() >= getTemplate()->energyCost() &&
           timeSinceLastCast_ >= coolDown_;
}

SkillButton *SkillWithCost::button()
{
    return button_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
