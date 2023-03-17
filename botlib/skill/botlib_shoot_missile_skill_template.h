#ifndef INCLUDED_BOTLIB_SHOOT_MISSILE_SKILL_TEMPLATE_H
#define INCLUDED_BOTLIB_SHOOT_MISSILE_SKILL_TEMPLATE_H

#include <botlib_skill_with_cost_template.h>

namespace mcdane {
namespace botlib {

class ShootMissileSkillTemplate: public SkillWithCostTemplate {
public:
    ShootMissileSkillTemplate();

    ShootMissileSkillTemplate(const rapidjson::Value &v,
                              const ProgressPieTemplateLib &progressPieLib);

    void init(const rapidjson::Value &v,
              const ProgressPieTemplateLib &progressPieLib);
};

} // end of namespace botlib
} // end of namespace mcdane

#endif
