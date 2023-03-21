#ifndef INCLUDED_BOTLIB_PARTCILE_EFFECT_H
#define INCLUDED_BOTLIB_PARTCILE_EFFECT_H

#include <commonlib_time_utils.h>
#include <botlib_particle_effect_template.h>
#include <botlib_game_object.h>

namespace mcdane {
namespace botlib {

class ParticleEffect: public GameObject {
public:
    ParticleEffect() = default;

    ParticleEffect(const ParticleEffectTemplate *t,
                   const commonlib::Vector2 &pos);

    ~ParticleEffect() override = default;

    void init(const ParticleEffectTemplate *t,
              const commonlib::Vector2 &pos);

    inline const ParticleEffectTemplate *getTemplate() const;

    void present() const override;

    void update(UpdateContext &cxt) override;

    bool canBeDumped(GameMap &map) const override;

private:
    float elapsedTime_;
};

const ParticleEffectTemplate *ParticleEffect::getTemplate() const
{
    return static_cast<const ParticleEffectTemplate*>(t_);
}

} // end of namespace botlib
} // end of namespace mcdane

#endif

