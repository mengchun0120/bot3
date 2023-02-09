#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_json_param.h>
#include <commonlib_named_map.h>
#include <botlib_missile_template.h>
#include <botlib_targeted_blast_skill_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

TargetedBlastSkillTemplate::TargetedBlastSkillTemplate(
                                   const rapidjson::Value& v,
                                   const MissileTemplateLib& missileLib,
                                   const ProgressPieTemplateLib& progressPieLib)
{
    init(v, missileLib, progressPieLib);
}

void TargetedBlastSkillTemplate::init(const rapidjson::Value& v,
                                      const MissileTemplateLib& missileLib,
                                      const ProgressPieTemplateLib& progressPieLib)
{
    SkillTemplate::init(SkillType::TARGETED_BLAST, v, progressPieLib);

    std::string missileName;
    std::vector<JsonParamPtr> params{
        jsonParam(missileName, {"missile"}, true, k_nonEmptyStrV),
        jsonParam(numTargets_, {"numTargets"}, true, gt(0)),
        jsonParam(searchRange_, {"searchRange"}, true, gt(0.0f)),
        jsonParam(startRadius_, {"startRadius"}, true, gt(0.0f)),
    };

    parse(params, v);

    missileTemplate_ = missileLib.search(missileName);
    if (!missileTemplate_)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Failed to find missile " + missileName);
    }
}

} // end of namespace botlib
} // end of namespace mcdane
