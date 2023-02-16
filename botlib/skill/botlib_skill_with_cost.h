#ifndef INCLUDED_BOTLIB_SKILL_WITH_COST_H
#define INCLUDED_BOTLIB_SKILL_WITH_COST_H

#include <botlib_robot.h>
#include <botlib_skill_with_cost_template.h>
#include <botlib_skill.h>

namespace mcdane {
namespace botlib {

class SkillWithCost: public Skill {
public:
    SkillWithCost();

    SkillWithCost(const SkillTemplate* t,
                  Robot* robot,
                  bool enabled1=false);

    ~SkillWithCost() override;

    void init(const SkillTemplate* t,
              Robot* robot,
              bool enabled1=false);

    inline const SkillWithCostTemplate* getTemplate() const;

    inline const ProgressPie* pie() const;

    inline int curIconIndex() const;

    inline bool available() const;

    void update(UpdateContext& cxt) override;

    void setCoolDownFactor(float f);

    void resetCoolDown();

protected:
    virtual bool apply(UpdateContext& cxt) = 0;

    void updatePie();

protected:
    float coolDown_;
    float timeSinceLastCast_;
    ProgressPie* pie_;
    int curIconIndex_;
};

const SkillWithCostTemplate* SkillWithCost::getTemplate() const
{
    return static_cast<const SkillWithCostTemplate*>(t_);
}

const ProgressPie* SkillWithCost::pie() const
{
    return pie_;
}

int SkillWithCost::curIconIndex() const
{
    return curIconIndex_;
}

bool SkillWithCost::available() const
{
    return robot_->energy() >= getTemplate()->energyCost() &&
           timeSinceLastCast_ >= coolDown_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
