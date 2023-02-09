#ifndef INCLUDED_BOTLIB_TARGETED_BLAST_SKILL_H
#define INCLUDED_BOTLIB_TARGETED_BLAST_SKILL_H

#include <commonlib_region.h>
#include <botlib_targeted_blast_skill_template.h>
#include <botlib_skill_with_cost.h>

namespace mcdane {
namespace botlib {

class TargetedBlastSkill: public SkillWithCost {
public:
    TargetedBlastSkill() = default;

    TargetedBlastSkill(const TargetedBlastSkillTemplate* t,
                       Robot* robot,
                       bool enabled1=false);

    ~TargetedBlastSkill() override = default;

    void init(const TargetedBlastSkillTemplate* t,
              Robot* robot,
              bool enabled1=false);

    inline const TargetedBlastSkillTemplate* getTemplate() const;

protected:
    bool apply(UpdateContext& cxt) override;

private:
    commonlib::Region<int> searchRegion(GameMap* map);

    void findTargets(GameObjItemList& targets,
                     UpdateContext& cxt);

    void shootTargets(GameObjItemList& targets,
                      UpdateContext& cxt);
};

const TargetedBlastSkillTemplate* TargetedBlastSkill::getTemplate() const
{
    return static_cast<const TargetedBlastSkillTemplate*>(t_);
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
