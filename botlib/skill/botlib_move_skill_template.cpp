#include <commonlib_json_param.h>
#include <botlib_move_skill_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

MoveSkillTemplate::MoveSkillTemplate()
    : SkillTemplate()
    , hasDest_(false)
{
}

MoveSkillTemplate::MoveSkillTemplate(const rapidjson::Value& v,
                                     const ProgressPieTemplateLib& progressPieLib)
{
    init(v, progressPieLib);
}

void MoveSkillTemplate::init(const rapidjson::Value& v,
                             const ProgressPieTemplateLib& progressPieLib)
{
    SkillTemplate::init(SkillType::MOVE, v, progressPieLib);

    std::vector<JsonParamPtr> params{
        jsonParam(hasDest_, "hasDest", false),
        jsonParam(speed_, "speed", true, gt(0.0f)),
    };

    parse(params, v);
}

} // end of namespace botlib
} // end of namespace mcdane
