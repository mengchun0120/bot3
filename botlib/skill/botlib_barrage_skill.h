#ifndef INCLUDED_BOTLIB_BARRAGE_SKILL_H
#define INCLUDED_BOTLIB_BARRAGE_SKILL_H

#include <botlib_barrage_skill_template.h>
#include <botlib_skill_with_cost.h>

namespace mcdane {
namespace botlib {

class BarrageSkill: public SkillWithCost {
public:
    BarrageSkill();

    BarrageSkill(const BarrageSkillTemplate *t,
                 Robot *robot,
                 bool enabled1=false,
                 const commonlib::Vector2 *buttonPos=nullptr);

    ~BarrageSkill() override = default;

    void init(const BarrageSkillTemplate *t,
              Robot *robot,
              bool enabled1=false,
              const commonlib::Vector2 *buttonPos=nullptr);

    inline const BarrageSkillTemplate *getTemplate() const;

private:
    bool apply(UpdateContext &cxt) override;

protected:
    int shootTimes_;
    float timeSinceLastShoot_;
};

const BarrageSkillTemplate *BarrageSkill::getTemplate() const
{
    return static_cast<const BarrageSkillTemplate*>(t_);
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
