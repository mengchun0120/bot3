#ifndef INCLUDED_BOTLIB_SKILL_WITH_COST_H
#define INCLUDED_BOTLIB_SKILL_WITH_COST_H

#include <botlib_skill.h>
#include <botlib_robot.h>

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

    inline const ProgressPie* pie() const;

    inline int curIconIndex() const;

    inline bool available() const;

    void update(UpdateContext& cxt) override;

    void setCoolDownFactor(float f);

    void resetCoolDown();

protected:
    virtual bool apply(UpdateContext& cxt) = 0;

    void updatePie();

    void checkEnabled();

protected:
    float coolDown_;
    float timeSinceLastCast_;
    ProgressPie* pie_;
    int curIconIndex_;
};

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
    return robot_->energy() >= t_->energyCost() &&
           timeSinceLastCast_ >= coolDown_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
