#ifndef INCLUDED_BOTLIB_BARRAGE_SKILL_TEMPLATE_H
#define INCLUDED_BOTLIB_BARRAGE_SKILL_TEMPLATE_H

#include <botlib_skill_with_cost_template.h>

namespace mcdane {
namespace botlib {

class BarrageSkillTemplate: public SkillWithCostTemplate {
public:
    BarrageSkillTemplate();

    BarrageSkillTemplate(const rapidjson::Value &v,
                         const ProgressPieTemplateLib &progressPieLib);

    void init(const rapidjson::Value &v,
              const ProgressPieTemplateLib &progressPieLib);

    inline int maxShootTimes() const;

    inline float shootInterval() const;

protected:
    int maxShootTimes_;
    float shootInterval_;
};

int BarrageSkillTemplate::maxShootTimes() const
{
    return maxShootTimes_;
}

float BarrageSkillTemplate::shootInterval() const
{
    return shootInterval_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
