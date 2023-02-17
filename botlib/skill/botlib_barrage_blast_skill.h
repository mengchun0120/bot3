#ifndef INCLUDED_BOTLIB_BARRAGE_BLAST_SKILL_H
#define INCLUDED_BOTLIB_BARRAGE_BLAST_SKILL_H

#include <botlib_barrage_blast_skill_template.h>
#include <botlib_skill_with_cost.h>

namespace mcdane {
namespace botlib {

class BarrageBlastSkill: public SkillWithCost {
public:
    BarrageBlastSkill();

    BarrageBlastSkill(const BarrageBlastSkillTemplate* t,
                      Robot* robot,
                      bool enabled1=false);

    ~BarrageBlastSkill() override = default;

    void init(const BarrageBlastSkillTemplate* t,
              Robot* robot,
              bool enabled1=false);

    inline const BarrageBlastSkillTemplate* getTemplate() const;

private:
    bool apply(UpdateContext& cxt) override;

    void blast(UpdateContext& cxt);

protected:
    int shootTimes_;
    float timeSinceLastShoot_;
};

const BarrageBlastSkillTemplate* BarrageBlastSkill::getTemplate() const
{
    return static_cast<const BarrageBlastSkillTemplate*>(t_);
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
