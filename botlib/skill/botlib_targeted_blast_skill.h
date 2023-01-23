#ifndef INCLUDED_BOTLIB_TARGETED_BLAST_SKILL_H
#define INCLUDED_BOTLIB_TARGETED_BLAST_SKILL_H

#include <botlib_targeted_blast_skill_template.h>
#include <botlib_skill.h>

namespace mcdane {
namespace botlib {

class TargetedBlastSkill: public Skill {
public:
    TargetedBlastSkill(const TargetedBlastSkillTemplate* t,
                       Robot* robot);

    inline const TargetBlastSkillTemplate* getTemplate() const;

    void update(UpdateContext& cxt) override;

    inline bool available() const;

private:
    void init(const TargetedBlastSkillTemplate* t,
              Robot* robot);

protected:
    float timeSinceLastBlast_;
};

const TargetBlastSkillTemplate* TargetedBlastSkill::getTemplate() const
{
    return static_cast<const TargetedBlastSkillTemplate*>(t_);
}

bool TargetedBlastSkill::available() const
{
    return enabled() &&
           t_->energyCost() <= robot_->energy() &&
           t_->coolDown() <= timeSinceLastBlast_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
