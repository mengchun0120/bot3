#include <sstream>
#include <botlib_particle_effect_template.h>
#include <botlib_missile_template.h>

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

std::string MissileTemplate::toString() const
{
    std::ostringstream oss;

    oss << "MissileTemplate(damage=" << damage_
        << ", speed=" << speed_
        << ", explodeBreath=" << explodeBreath_
        << ", explodeEffectTemplate=" << explodeEffectTemplate_->toString()
        << ", Base=" << CompositeObjectTemplate::toString()
        << ")";

    return oss.str();
}

} // end of namespace botlib
} // end of namespace mcdane

