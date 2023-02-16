#ifndef INCLUDED_BOTLIB_TARGETED_BLAST_SKILL_TEMPLATE_H
#define INCLUDED_BOTLIB_TARGETED_BLAST_SKILL_TEMPLATE_H

#include <botlib_skill_with_cost_template.h>

namespace mcdane {
namespace botlib {

class TargetedBlastSkillTemplate: public SkillWithCostTemplate {
public:
    TargetedBlastSkillTemplate();

    TargetedBlastSkillTemplate(const rapidjson::Value& v,
                               const ProgressPieTemplateLib& progressPieLib);

    void init(const rapidjson::Value& v,
              const ProgressPieTemplateLib& progressPieLib);

    inline int numTargets() const;

    inline float searchRange() const;

    inline float startRadius() const;

protected:
    int numTargets_;
    float searchRange_;
    float startRadius_;
};

int TargetedBlastSkillTemplate::numTargets() const
{
    return numTargets_;
}

float TargetedBlastSkillTemplate::searchRange() const
{
    return searchRange_;
}

float TargetedBlastSkillTemplate::startRadius() const
{
    return startRadius_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
