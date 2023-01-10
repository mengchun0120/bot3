#ifndef INCLUDED_BOTLIB_SHOOT_MISSILE_SKILL_TEMPLATE_H
#define INCLUDED_BOTLIB_SHOOT_MISSILE_SKILL_TEMPLATE_H

#include <botlib_skill_template.h>

namespace mcdane {
namespace botlib {

class ShootMissileSkillTemplate: public SkillTemplate {
public:
    ShootMissileSkillTemplate() = default;

    void init(const rapidjson::Value& v);
};

} // end of namespace botlib
} // end of namespace mcdane

#endif
