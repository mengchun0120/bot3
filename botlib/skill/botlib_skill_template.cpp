#include <commonlib_exception.h>
#include <commonlib_json_param.h>
#include <botlib_skill_flag.h>
#include <botlib_skill_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

SkillTemplate::SkillTemplate()
    : flags_(0)
    , coolDown_(0.0f)
    , energyCost_(0.0f)
{
}

void SkillTemplate::init(SkillType type, const rapidjson::Value& v)
{
    type_ = type;

    bool isOffensive = false;
    std::vector<JsonParamPtr> params{
        jsonParam(isOffensive, "isOffensive", false),
        jsonParam(coolDown_, "coolDown", false, ge(0.0f)),
        jsonParam(energyCost_, "energyCost", false, ge(0.0f)),
    };

    parse(params, v);

    if (isOffensive)
    {
        flags_ = flags_ | SkillFlag::OFFENSIVE;
    }
}

} // end of namespace botlib
} // end of namespace mcdane
