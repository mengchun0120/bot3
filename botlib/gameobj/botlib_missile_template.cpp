#include <commonlib_exception.h>
#include <commonlib_json_param.h>
#include <commonlib_named_map.h>
#include <botlib_particle_effect_template.h>
#include <botlib_missile_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

MissileTemplate::MissileTemplate()
    : damage_(0.0f)
    , speed_(0.0f)
    , explodeBreath_(0.0f)
    , energyCost_(0.0f)
    , duration_(0.0f)
    , explodeEffectTemplate_(nullptr)
    , searchBreath_(0.0f)
    , splitCount_(0)
    , splitMissileTemplate_(nullptr)
{
}

void MissileTemplate::init(
    const std::string &name,
    const rapidjson::Value &v,
    const ParticleEffectTemplateLib &particleEffectTemplateLib,
    const ComponentTemplateLib &componentTemplateLib,
    const MissileTemplateLib &missileTemplateLib)
{
    std::string explodeEffectName, splitMissileName;
    std::vector<JsonParamPtr> params{
        jsonParam(damage_, "damage", true, gt(0.0f)),
        jsonParam(speed_, "speed", true, gt(0.0f)),
        jsonParam(explodeBreath_, "explodeBreath", true, gt(0.0f)),
        jsonParam(energyCost_, "energyCost", true, ge(0.0f)),
        jsonParam(duration_, "duration", true, gt(0.0f)),
        jsonParam(explodeEffectName, "explodeEffect", true, k_nonEmptyStrV),
        jsonParam(searchBreath_, "searchBreath", false, ge(0.0f)),
        jsonParam(splitCount_, "splitCount", false, ge(0)),
        jsonParam(splitMissileName, "splitMissile", false, k_nonEmptyStrV),
        jsonParam(splitMissileDirections_, "splitMissileDirections", false)
    };

    parse(params, v);

    explodeEffectTemplate_ = particleEffectTemplateLib.search(explodeEffectName);
    if (!explodeEffectTemplate_)
    {
        THROW_EXCEPT(ParseException,
                     "Failed to find explode effect " + explodeEffectName);
    }

    if (splitCount_ > 0 && splitMissileName.empty())
    {
        THROW_EXCEPT(ParseException,
                     "splitMissile is not specified");
    }

    if (!splitMissileName.empty())
    {
        splitMissileTemplate_ = missileTemplateLib.search(splitMissileName);
        if (!splitMissileTemplate_)
        {
            THROW_EXCEPT(ParseException,
                         "Failed to find missile " + splitMissileName);
        }
    }

    if (static_cast<int>(splitMissileDirections_.size()) != splitCount_)
    {
        THROW_EXCEPT(ParseException,
                     "Size of splitMissileDirections doesn't match splitCount");
    }

    CompositeObjectTemplate::init(GameObjectType::MISSILE, name,
                                  v, componentTemplateLib);
}

} // end of namespace botlib
} // end of namespace mcdane

