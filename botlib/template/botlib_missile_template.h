#ifndef INCLUDED_BOTLIB_MISSILE_TEMPLATE_H
#define INCLUDED_BOTLIB_MISSILE_TEMPLATE_H

#include <botlib_composite_object_template.h>

namespace mcdane {
namespace botlib {

class ParticleEffectTemplate;

class MissileTemplate: public CompositeObjectTemplate {
public:
    MissileTemplate() = default;

    MissileTemplate(float collideBreath1,
                    float damage1,
                    float speed1,
                    float explodeBreath1,
                    const ParticleEffectTemplate* explodeEffectTemplate1,
                    std::vector<Component>&& components);

    ~MissileTemplate() override = default;

    void init(const rapidjson::Value& v,
              const ParticleEffectTemplateLib& particleEffectTemplateLib,
              const ComponentTemplateLib& componentTemplateLib);

    inline float damage() const;

    inline float speed() const;

    inline float explodeBreath() const;

    inline const ParticleEffectTemplate* explodeEffectTemplate() const;

private:
    float damage_;
    float speed_;
    float explodeBreath_;
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

const ParticleEffectTemplate* MissileTemplate::explodeEffectTemplate() const
{
    return explodeEffectTemplate_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

