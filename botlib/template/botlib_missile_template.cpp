#include <commonlib_exception.h>
#include <commonlib_json_param.h>
#include <commonlib_named_map.h>
#include <botlib_particle_effect_template.h>
#include <botlib_missile_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

MissileTemplate::MissileTemplate(
                    float collideBreath1,
                    float damage1,
                    float speed1,
                    float explodeBreath1,
                    const ParticleEffectTemplate* explodeEffectTemplate1,
                    std::vector<Component>&& components)
    : CompositeObjectTemplate(
        GameObjectType::MISSILE,
        collideBreath1,
        false,
        std::forward<std::vector<Component>>(components))
    , damage_(damage1)
    , speed_(speed1)
    , explodeBreath_(explodeBreath1)
    , explodeEffectTemplate_(explodeEffectTemplate1)
{
}

void MissileTemplate::init(
    const rapidjson::Value& v,
    const ParticleEffectTemplateLib& particleEffectTemplateLib,
    const ComponentTemplateLib& componentTemplateLib)
{
    std::string explodeEffectName;
    std::vector<JsonParamPtr> params{
        jsonParam(damage_, "damage", true, gt(0.0f)),
        jsonParam(speed_, "speed", true, gt(0.0f)),
        jsonParam(explodeBreath_, "explodeBreath", true, gt(0.0f)),
        jsonParam(explodeEffectName, "explodeEffect", true, k_nonEmptyStrV)
    };

    parse(params, v);

    explodeEffectTemplate_ = particleEffectTemplateLib.search(explodeEffectName);
    if (!explodeEffectTemplate_)
    {
        THROW_EXCEPT(ParseException,
                     "Failed to find explode effect " + explodeEffectName);
    }

    CompositeObjectTemplate::init(GameObjectType::MISSILE, v, componentTemplateLib);
}

} // end of namespace botlib
} // end of namespace mcdane

