#ifndef INCLUDED_BOTLIB_TARGETED_BLAST_SKILL_H
#define INCLUDED_BOTLIB_TARGETED_BLAST_SKILL_H

#include <commonlib_region.h>
#include <botlib_typedef.h>
#include <botlib_targeted_blast_skill_template.h>
#include <botlib_skill.h>

namespace mcdane {
namespace botlib {

class TargetedBlastSkill: public Skill {
public:
    TargetedBlastSkill(const TargetedBlastSkillTemplate* t,
                       Robot* robot);

    inline const TargetedBlastSkillTemplate* getTemplate() const;

    void update(UpdateContext& cxt) override;

    inline bool available() const;

private:
    void init(const TargetedBlastSkillTemplate* t,
              Robot* robot);

    commonlib::Region<int> searchRegion(GameMap* map);

    void findTargets(GameObjItemList& targets, UpdateContext& cxt);

    void shootTargets(GameObjItemList& targets, UpdateContext& cxt);

    inline void checkEnabled();

protected:
    float timeSinceLastBlast_;
};

const TargetedBlastSkillTemplate* TargetedBlastSkill::getTemplate() const
{
    return static_cast<const TargetedBlastSkillTemplate*>(t_);
}

bool TargetedBlastSkill::available() const
{
    return enabled() &&
           t_->energyCost() <= robot_->energy() &&
           t_->coolDown() <= timeSinceLastBlast_;
}

void TargetedBlastSkill::checkEnabled()
{
    if (!getTemplate()->keepAlive())
    {
        setEnabled(false);
    }
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
