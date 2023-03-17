#include <commonlib_exception.h>
#include <commonlib_json_param.h>
#include <botlib_skill_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

SkillTemplate::SkillTemplate()
    : flags_(0)
{
}

void SkillTemplate::init(SkillType type,
                         const rapidjson::Value &v)
{
    type_ = type;

    bool isOffensive = false, keepAlive = false;
    std::vector<JsonParamPtr> params{
        jsonParam(isOffensive, "isOffensive", false),
        jsonParam(keepAlive, "keepAlive", false),
    };

    parse(params, v);

    if (isOffensive)
    {
        flags_ = flags_ | StaticSkillFlag::OFFENSIVE;
    }

    if (keepAlive)
    {
        flags_ = flags_ | StaticSkillFlag::KEEPALIVE;
    }
}

} // end of namespace botlib
} // end of namespace mcdane
