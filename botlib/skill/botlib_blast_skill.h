#ifndef INCLUDED_BOTLIB_BLAST_SKILL_H
#define INCLUDED_BOTLIB_BLAST_SKILL_H

#include <botlib_blast_skill_template.h>
#include <botlib_skill.h>

namespace mcdane {
namespace botlib {

class BlastSkill: public Skill {
public:
    BlastSkill();

    BlastSkill(const BlastSkillTemplate *t, Robot* robot);

    void init(const BlastSkillTemplate *t, Robot* robot);

    inline const BlastSkillTemplate* getTemplate() const;

    inline bool available() const;

    void update(UpdateContext& cxt) override;

protected:
    float timeSinceLastBlast_;
};

const BlastSkillTemplate* BlastSkill::getTemplate() const
{
    return static_cast<const BlastSkillTemplate*>(t_);
}

bool BlastSkill::available() const
{
    return enabled() &&
           t_->energyCost() <= robot_->energy() &&
           t_->coolDown() <= timeSinceLastBlast_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
