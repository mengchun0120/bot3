#include <commonlib_exception.h>
#include <commonlib_named_map.h>
#include <botlib_particle_effect_template.h>
#include <botlib_component_template.h>
#include <botlib_missile_template.h>
#include <botlib_missile_template_parser.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

MissileTemplateParser::MissileTemplateParser(
            const ComponentTemplateLib& componentTemplateLib,
            const ParticleEffectTemplateLib& particleEffectTemplateLib)
    : CompositeObjectTemplateParser(componentTemplateLib)
    , particleEffectTemplateLib_(particleEffectTemplateLib)
    , params_{
        jsonParam(damage_, "damage", true, gt(0.0f)),
        jsonParam(speed_, "speed", true, gt(0.0f)),
        jsonParam(explodeBreath_, "explodeBreath", true, gt(0.0f)),
        jsonParam(explodeEffectName_, "explodeEffect", true, k_nonEmptyStrV)
      }
{
}

MissileTemplate* MissileTemplateParser::operator()(const rapidjson::Value& v)
{
    CompositeObjectTemplateParser::load(v);
    parse(params_, v);

    const ParticleEffectTemplate* explodeEffectTemplate =
                        particleEffectTemplateLib_.search(explodeEffectName_);
    if (!explodeEffectTemplate)
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "Cannot find ParticleEffectTemplate" + explodeEffectName_);
    }

    return new MissileTemplate(collideBreath_,
                               damage_,
                               speed_,
                               explodeBreath_,
                               explodeEffectTemplate,
                               std::move(components_));
}

} // end of namespace botlib
} // end of namespace mcdane

