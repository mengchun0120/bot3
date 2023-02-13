#ifndef INCLUDED_BOTLIB_BARRAGE_SKILL_TEMPLATE_H
#define INCLUDED_BOTLIB_BARRAGE_SKILL_TEMPLATE_H

#include <botlib_skill_template.h>

namespace mcdane {
namespace botlib {

class BarrageSkillTemplate: public SkillTemplate {
public:
    SkillTemplate();

    SkillTemplate(SkillType type,
                  const rapidjson::Value& v,
                  const MissileTemplateLib& missileLib,
                  const ProgressPieTemplateLib& progressPieLib);

    void init(SkillType type,
              const rapidjson::Value& v,
              const MissileTemplateLib& missileLib,
              const ProgressPieTemplateLib& progressPieLib);

protected:
    const MissileTemplate* missileTemplate_;
    
};

} // end of namespace botlib
} // end of namespace mcdane

#endif
