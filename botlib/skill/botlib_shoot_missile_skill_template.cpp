#include <commonlib_log.h>
#include <commonlib_json_param.h>
#include <botlib_shoot_missile_skill_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

ShootMissileSkillTemplate::ShootMissileSkillTemplate()
    : SkillTemplate()
    , keepAlive_(false)
{
}

ShootMissileSkillTemplate::ShootMissileSkillTemplate(
                                const rapidjson::Value& v,
                                const ProgressPieTemplateLib& progressPieLib)
{
    init(v, progressPieLib);
}

void ShootMissileSkillTemplate::init(const rapidjson::Value& v,
                                     const ProgressPieTemplateLib& progressPieLib)
{
    SkillTemplate::init(SkillType::SHOOT_MISSILE, v, progressPieLib);

    std::vector<JsonParamPtr> params{
        jsonParam(keepAlive_, "keepAlive", false),
    };
}

} // end of namespace botlib
} // end of namespace mcdane
