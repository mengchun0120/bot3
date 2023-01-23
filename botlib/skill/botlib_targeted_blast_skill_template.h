#ifndef INCLUDED_BOTLIB_TARGETED_BLAST_SKILL_TEMPLATE_H
#define INCLUDED_BOTLIB_TARGETED_BLAST_SKILL_TEMPLATE_H

#include <botlib_typedef.h>
#include <botlib_skill_template.h>

namespace mcdane {
namespace botlib {

class TargetedBlastSkillTemplate: public SkillTemplate {
public:
    TargetedBlastSkillTemplate(const rapidjson::Value& v,
                               const MissileTemplateLib& missileLib);

    inline const MissileTemplate* missileTemplate() const;

    inline int numTargets() const;

    inline float searchRange() const;

    inline float startRadius() const;

    inline bool keepAlive() const;

private:
    void init(const rapidjson::Value& v,
              const MissileTemplateLib& missileLib);

protected:
    const MissileTemplate* missileTemplate_;
    int numTargets_;
    float searchRange_;
    float startRadius_;
    bool keepAlive_;
};

const MissileTemplate* TargetedBlastSkillTemplate::missileTemplate() const
{
    return missileTemplate_;
}

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

bool TargetedBlastSkillTemplate::keepAlive() const
{
    return keepAlive_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
