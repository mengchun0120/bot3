#include <botlib_shoot_missile_skill_template.h>

namespace mcdane {
namespace botlib {

ShootMissileSkillTemplate::ShootMissileSkillTemplate()
    : SkillTemplate()
{
}

ShootMissileSkillTemplate::ShootMissileSkillTemplate(const rapidjson::Value& v)
{
    init(v);
}

void ShootMissileSkillTemplate::init(const rapidjson::Value& v)
{
    SkillTemplate::init(SkillType::SHOOT_MISSILE, v);
}

} // end of namespace botlib
} // end of namespace mcdane
