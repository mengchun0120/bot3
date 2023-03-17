#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_json_param.h>
#include <commonlib_named_map.h>
#include <botlib_missile_template.h>
#include <botlib_shoot_missile_skill_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

ShootMissileSkillTemplate::ShootMissileSkillTemplate()
    : SkillWithCostTemplate()
{
}

ShootMissileSkillTemplate::ShootMissileSkillTemplate(
                                const rapidjson::Value &v,
                                const ProgressPieTemplateLib &progressPieLib)
{
    init(v, progressPieLib);
}

void ShootMissileSkillTemplate::init(const rapidjson::Value &v,
                                     const ProgressPieTemplateLib &progressPieLib)
{
    SkillWithCostTemplate::init(SkillType::SHOOT_MISSILE, v, progressPieLib);
}

} // end of namespace botlib
} // end of namespace mcdane
