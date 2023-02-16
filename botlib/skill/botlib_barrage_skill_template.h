#ifndef INCLUDED_BOTLIB_BARRAGE_SKILL_TEMPLATE_H
#define INCLUDED_BOTLIB_BARRAGE_SKILL_TEMPLATE_H

#include <botlib_skill_with_cost_template.h>

namespace mcdane {
namespace botlib {

class BarrageSkillTemplate: public SkillWithCostTemplate {
public:
    BarrageSkillTemplate();

    BarrageSkillTemplate(const rapidjson::Value& v,
                         const MissileTemplateLib& missileLib,
                         const ProgressPieTemplateLib& progressPieLib);

    void init(const rapidjson::Value& v,
              const MissileTemplateLib& missileLib,
              const ProgressPieTemplateLib& progressPieLib);

    inline const MissileTemplate* missileTemplate() const;

    inline int numMissiles() const;

    inline float shootInterval() const;

protected:
    const MissileTemplate* missileTemplate_;
    int numMissiles_;
    float shootInterval_;
};

const MissileTemplate* BarrageSkillTemplate::missileTemplate() const
{
    return missileTemplate_;
}

int BarrageSkillTemplate::numMissiles() const
{
    return numMissiles_;
}

float BarrageSkillTemplate::shootInterval() const
{
    return shootInterval_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
