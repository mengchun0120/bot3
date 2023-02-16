#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_json_param.h>
#include <commonlib_named_map.h>
#include <botlib_missile_template.h>
#include <botlib_barrage_skill_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

BarrageSkillTemplate::BarrageSkillTemplate()
    : SkillWithCostTemplate()
    , missileTemplate_(nullptr)
    , numMissiles_(0)
    , shootInterval_(0.0f)
{
}

BarrageSkillTemplate::BarrageSkillTemplate(
                            const rapidjson::Value& v,
                            const MissileTemplateLib& missileLib,
                            const ProgressPieTemplateLib& progressPieLib)
{
    init(v, missileLib, progressPieLib);
}

void BarrageSkillTemplate::init(
                            const rapidjson::Value& v,
                            const MissileTemplateLib& missileLib,
                            const ProgressPieTemplateLib& progressPieLib)
{
    SkillWithCostTemplate::init(SkillType::BARRAGE, v, progressPieLib);

    std::string missileName;
    std::vector<JsonParamPtr> params{
        jsonParam(missileName, "missile", true, k_nonEmptyStrV),
        jsonParam(numMissiles_, "numMissiles", true, gt(0)),
        jsonParam(shootInterval_, "shootInterval", true, gt(0.0f)),
    };

    parse(params, v);

    missileTemplate_ = missileLib.search(missileName);
    if (!missileTemplate_)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Failed to find MissileTemplate " + missileName);
    }
}

} // end of namespace botlib
} // end of namespace mcdane
