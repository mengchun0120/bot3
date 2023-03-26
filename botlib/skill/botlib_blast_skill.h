#ifndef INCLUDED_BOTLIB_BLAST_SKILL_H
#define INCLUDED_BOTLIB_BLAST_SKILL_H

#include <botlib_blast_skill_template.h>
#include <botlib_skill_with_cost.h>

namespace mcdane {
namespace botlib {

class BlastSkill: public SkillWithCost {
public:
    BlastSkill() = default;

    BlastSkill(const BlastSkillTemplate *t,
               Robot *robot,
               bool enabled1=false,
               const commonlib::Vector2 *buttonPos=nullptr);

    ~BlastSkill() override = default;

    void init(const BlastSkillTemplate *t,
              Robot *robot,
              bool enabled1=false,
              const commonlib::Vector2 *buttonPos=nullptr);

    inline const BlastSkillTemplate *getTemplate() const;

protected:
    bool apply(UpdateContext &cxt) override;
};

const BlastSkillTemplate *BlastSkill::getTemplate() const
{
    return static_cast<const BlastSkillTemplate*>(t_);
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
