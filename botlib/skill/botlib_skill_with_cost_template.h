#ifndef INCLUDED_BOTLIB_SKILL_WITH_COST_TEMPLATE_H
#define INCLUDED_BOTLIB_SKILL_WITH_COST_TEMPLATE_H

#include <botlib_typedef.h>
#include <botlib_skill_template.h>

namespace mcdane {
namespace botlib {

class SkillWithCostTemplate: public SkillTemplate {
public:
    SkillWithCostTemplate();

    SkillWithCostTemplate(SkillType type,
                          const rapidjson::Value& v,
                          const ProgressPieTemplateLib& progressPieLib);

    void init(SkillType type,
              const rapidjson::Value& v,
              const ProgressPieTemplateLib& progressPieLib);

    inline float coolDown() const;

    inline float energyCost() const;

    inline const ProgressPieTemplate* pieTemplate() const;

private:
    void initPie(const std::string& pieName,
                 const ProgressPieTemplateLib& progressPieLib);

protected:
    float coolDown_;
    float energyCost_;
    const ProgressPieTemplate* pieTemplate_;
};

float SkillWithCostTemplate::coolDown() const
{
    return coolDown_;
}

float SkillWithCostTemplate::energyCost() const
{
    return energyCost_;
}

const ProgressPieTemplate* SkillWithCostTemplate::pieTemplate() const
{
    return pieTemplate_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
