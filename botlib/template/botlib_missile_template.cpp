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

rapidjson::Value MissileTemplate::toJson(
                rapidjson::Document::AllocatorType& allocator) const
{
    using namespace rapidjson;

    Value v(kObjectType);

    v.AddMember("class", "MissileTemplate", allocator);
    v.AddMember("damage", damage_, allocator);
    v.AddMember("speed", speed_, allocator);
    v.AddMember("explodeBreath", explodeBreath_, allocator);
    v.AddMember("particleEffectTemplate", explodeEffectTemplate_->id(),
                allocator);
    v.AddMember("base", CompositeObjectTemplate::toJson(allocator), allocator);

    return v;
}

} // end of namespace botlib
} // end of namespace mcdane

