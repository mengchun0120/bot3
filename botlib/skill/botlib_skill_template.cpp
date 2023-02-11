#include <commonlib_exception.h>
#include <commonlib_json_param.h>
#include <commonlib_named_map.h>
#include <botlib_progress_pie_template.h>
#include <botlib_skill_flag.h>
#include <botlib_skill_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

SkillTemplate::SkillTemplate()
    : flags_(0)
    , coolDown_(0.0f)
    , energyCost_(0.0f)
    , keepAlive_(false)
    , pieTemplate_(nullptr)
{
}

void SkillTemplate::init(SkillType type,
                         const rapidjson::Value& v,
                         const ProgressPieTemplateLib& progressPieLib)
{
    type_ = type;

    bool isOffensive = false;
    std::string pieName;
    std::vector<JsonParamPtr> params{
        jsonParam(isOffensive, "isOffensive", false),
        jsonParam(coolDown_, "coolDown", false, ge(0.0f)),
        jsonParam(energyCost_, "energyCost", false, ge(0.0f)),
        jsonParam(keepAlive_, "keepAlive", false),
        jsonParam(pieName, "pie", false, k_nonEmptyStrV),
    };

    parse(params, v);

    if (isOffensive)
    {
        flags_ = flags_ | SkillFlag::OFFENSIVE;
    }

    initPie(pieName, progressPieLib);
}

void SkillTemplate::initPie(const std::string& pieName,
                            const ProgressPieTemplateLib& progressPieLib)
{
    if (pieName.empty())
    {
        return;
    }

    pieTemplate_ = progressPieLib.search(pieName);
    if (!pieTemplate_)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Failed to find ProgressPie " + pieName);
    }

    if (pieTemplate_->numIcons() < 2)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "ProgressPie for skill must have at least two icons");
    }
}

} // end of namespace botlib
} // end of namespace mcdane
