#ifndef INCLUDED_BOTLIB_MISSILE_TEMPLATE_H
#define INCLUDED_BOTLIB_MISSILE_TEMPLATE_H

#include <botlib_composite_object_template.h>

namespace mcdane {
namespace botlib {

class ParticleEffectTemplate;

class MissileTemplate: public CompositeObjectTemplate {
public:
    MissileTemplate() = default;

    ~MissileTemplate() override = default;

    void init(const std::string& name,
              const rapidjson::Value& v,
              const ParticleEffectTemplateLib& particleEffectTemplateLib,
              const ComponentTemplateLib& componentTemplateLib);

    inline float damage() const;

    inline float speed() const;

    inline float explodeBreath() const;

    inline float energyCost() const;

    inline float duration() const;

    inline const ParticleEffectTemplate* explodeEffectTemplate() const;

private:
    float damage_;
    float speed_;
    float explodeBreath_;
    float energyCost_;
    float duration_;
    const ParticleEffectTemplate* explodeEffectTemplate_;
};

float MissileTemplate::damage() const
{
    return damage_;
}

float MissileTemplate::speed() const
{
    return speed_;
}

float MissileTemplate::explodeBreath() const
{
    return explodeBreath_;
}

float MissileTemplate::energyCost() const
{
    return energyCost_;
}

float MissileTemplate::duration() const
{
    return duration_;
}

const ParticleEffectTemplate* MissileTemplate::explodeEffectTemplate() const
{
    return explodeEffectTemplate_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

