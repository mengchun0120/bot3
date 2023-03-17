#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_json_param.h>
#include <botlib_barrage_skill_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

BarrageSkillTemplate::BarrageSkillTemplate()
    : SkillWithCostTemplate()
    , maxShootTimes_(0)
    , shootInterval_(0.0f)
{
}

BarrageSkillTemplate::BarrageSkillTemplate(
                            const rapidjson::Value &v,
                            const ProgressPieTemplateLib &progressPieLib)
{
    init(v, progressPieLib);
}

void BarrageSkillTemplate::init(
                            const rapidjson::Value &v,
                            const ProgressPieTemplateLib &progressPieLib)
{
    SkillWithCostTemplate::init(SkillType::BARRAGE, v, progressPieLib);

    std::vector<JsonParamPtr> params{
        jsonParam(maxShootTimes_, "maxShootTimes", true, gt(0)),
        jsonParam(shootInterval_, "shootInterval", true, gt(0.0f)),
    };

    parse(params, v);
}

} // end of namespace botlib
} // end of namespace mcdane
