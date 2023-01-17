#ifndef INCLUDED_BOTLIB_SHOOT_MISSILE_SKILL_TEMPLATE_H
#define INCLUDED_BOTLIB_SHOOT_MISSILE_SKILL_TEMPLATE_H

#include <botlib_skill_template.h>

namespace mcdane {
namespace botlib {

class ShootMissileSkillTemplate: public SkillTemplate {
public:
    ShootMissileSkillTemplate();

    ShootMissileSkillTemplate(const rapidjson::Value& v);

    void init(const rapidjson::Value& v);

    inline bool keepAlive() const;

protected:
    bool keepAlive_;
};

bool ShootMissileSkillTemplate::keepAlive() const
{
    return keepAlive_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
