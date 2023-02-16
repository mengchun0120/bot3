#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_json_param.h>
#include <commonlib_named_map.h>
#include <botlib_missile_template.h>
#include <botlib_targeted_blast_skill_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

TargetedBlastSkillTemplate::TargetedBlastSkillTemplate()
    : SkillWithCostTemplate()
    , numTargets_(0)
    , searchRange_(0.0f)
    , startRadius_(0.0f)
{
}

TargetedBlastSkillTemplate::TargetedBlastSkillTemplate(
                                   const rapidjson::Value& v,
                                   const ProgressPieTemplateLib& progressPieLib)
{
    init(v, progressPieLib);
}

void TargetedBlastSkillTemplate::init(const rapidjson::Value& v,
                                      const ProgressPieTemplateLib& progressPieLib)
{
    SkillWithCostTemplate::init(SkillType::TARGETED_BLAST, v, progressPieLib);

    std::string missileName;
    std::vector<JsonParamPtr> params{
        jsonParam(numTargets_, "numTargets", true, gt(0)),
        jsonParam(searchRange_, "searchRange", true, gt(0.0f)),
        jsonParam(startRadius_, "startRadius", true, gt(0.0f)),
    };

    parse(params, v);
}

} // end of namespace botlib
} // end of namespace mcdane
