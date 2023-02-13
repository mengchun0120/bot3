#include <commonlib_log.h>
#include <commonlib_exception.h>
#include <commonlib_json_utils.h>
#include <commonlib_named_map.h>
#include <botlib_progress_pie_template.h>
#include <botlib_skill_with_cost_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

SkillWithCostTemplate::SkillWithCostTemplate()
    : SkillTemplate()
    , coolDown_(0.0f)
    , energyCost_(0.0f)
    , pieTemplate_(nullptr)
{
}

SkillWithCostTemplate::SkillWithCostTemplate(
                                 SkillType type,
                                 const rapidjson::Value& v,
                                 const ProgressPieTemplateLib& progressPieLib)
{
    init(type, v, progressPieLib);
}

void SkillWithCostTemplate::init(SkillType type,
                                 const rapidjson::Value& v,
                                 const ProgressPieTemplateLib& progressPieLib)
{
    SkillTemplate::init(type, v);

    std::string pieName;
    std::vector<JsonParamPtr> params{
        jsonParam(coolDown_, "coolDown", true, ge(0.0f)),
        jsonParam(energyCost_, "energyCost", true, ge(0.0f)),
        jsonParam(pieName, "pie", false, k_nonEmptyStrV),
    };

    parse(params, v);

    LOG_INFO << "pie " << pieName << LOG_END;

    initPie(pieName, progressPieLib);
}

void SkillWithCostTemplate::initPie(
                                const std::string& pieName,
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
