#include <commonlib_log.h>
#include <commonlib_json_param.h>
#include <botlib_targeted_blast_skill_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

TargetedBlastSkillTemplate::TargetedBlastSkillTemplate(const rapidjson::Value& v)
{
    init(v);
}

void TargetedBlastSkillTemplate::init(const rapidjson::Value& v)
{
    SkillTemplate::init(SkillType::TARGETED_BLAST, v);

    std::vector<JsonParamPtr> params{
        jsonParam(numTargets_, {"numTargets"}, true, gt(0)),
        jsonParam(searchRange_, {"searchRange"}, true, gt(0.0f)),
        jsonParam(startRadius_, {"startRadius"}, true, gt(0.0f)),
        jsonParam(keepAlive_, {"keepAlive"}, true),
    };

    parse(params, v);
}

} // end of namespace botlib
} // end of namespace mcdane
