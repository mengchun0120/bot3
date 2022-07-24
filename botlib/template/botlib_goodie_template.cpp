#include <commonlib_exception.h>
#include <commonlib_json_param.h>
#include <commonlib_named_map.h>
#include <botlib_progress_pie_template.h>
#include <botlib_goodie_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void GoodieTemplate::init(GoodieType goodieType1,
                          const rapidjson::Value& v,
                          const ComponentTemplateLib& componentTemplateLib,
                          const ProgressPieTemplateLib& progressPieTemplateLib)
{
    if (!isValid(goodieType1))
    {
        THROW_EXCEPT(InvalidArgumentException, "Invalid GoodieType");
    }

    goodieType_ = goodieType1;

    std::string pieName;
    std::vector<JsonParamPtr> params{
        jsonParam(duration_, {"duration"}, true, ge(0.0f)),
        jsonParam(weight_, {"weight"}, true, gt(0.0f)),
        jsonParam(factor_, {"factor"}, false),
        jsonParam(pieName, {"progressPie"}, false)
    };

    parse(params, v);

    if (!pieName.empty())
    {
        progressPieTemplate_ = progressPieTemplateLib.search(pieName);
        if (!progressPieTemplate_)
        {
            THROW_EXCEPT(InvalidArgumentException,
                         "Failed to find progressPieTemplate: " + pieName);
        }
    }
    else
    {
        progressPieTemplate_ = nullptr;
    }

    CompositeObjectTemplate::init(GameObjectType::GOODIE, v, componentTemplateLib);

    initActions();
}

void GoodieTemplate::initActions()
{
    switch(goodieType_)
    {
        case GoodieType::HEALTH_FILLER:
        {
            activateAction_ = activateHealthFiller;
            break;
        }
        case GoodieType::ATTACK_ACCELERATOR:
        {
            activateAction_ = activateAttackAccelerator;
            deactivateAction_ = deactivateAttackAccelerator;
            break;
        }
        case GoodieType::SPEED_ACCELERATOR:
        {
            activateAction_ = activateSpeedAccelerator;
            deactivateAction_ = deactivateSpeedAccelerator;
            break;
        }
        case GoodieType::ARMOR_ENHANCER:
        {
            activateAction_ = activateArmorEnhancer;
            deactivateAction_ = deactivateArmorEnhancer;
            break;
        }
        case GoodieType::DAMAGE_AMPLIFIER:
        {
            activateAction_ = activateDamageAmplifier;
            deactivateAction_ = deactivateDamageAmplifier;
            break;
        }
        default:
            THROW_EXCEPT(InvalidArgumentException, "Invalid goodieType");
            break;
    }
}

} // end of namespace botlib
} // end of namespace mcdane

