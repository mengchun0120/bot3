#include <commonlib_log.h>
#include <botlib_context.h>
#include <botlib_update_context.h>
#include <botlib_game_map.h>
#include <botlib_game_object_dumper.h>
#include <botlib_particle_effect.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

ParticleEffect::ParticleEffect(const ParticleEffectTemplate* t,
                               const commonlib::Vector2& pos)
{
    init(t, pos);
}

void ParticleEffect::init(const ParticleEffectTemplate* t,
                          const Vector2& pos)
{
    GameObject::init(t, pos);
    startTime_ = Clock::now();
    elapsedTime_ = 0.0f;
}

void ParticleEffect::present() const
{
    ParticleShaderProgram& shader = Context::graphics().particleShader();
    const ParticleEffectTemplate* t = getTemplate();

    shader.setRef(pos_);
    shader.setAcceleration(t->acceleration());
    shader.setParticleSize(t->particleSize());
    shader.setCurTime(elapsedTime_);
    shader.setDuration(t->duration());
    shader.setStartPosDirectionSpeed(t->vertexArray());
    shader.setPointTexture(t->texture()->id());
    shader.setColor(t->color());

    glDrawArrays(GL_POINTS, 0, t->numParticles());
}

void ParticleEffect::update(UpdateContext& cxt)
{
    if (state_ == GameObjectState::ALIVE)
    {
        elapsedTime_ += cxt.timeDelta();
        if (elapsedTime_ >= getTemplate()->duration())
        {
            cxt.dumper().add(this);
        }
    }

    GameObject::update(cxt);
}

bool ParticleEffect::canBeDumped(GameMap& map) const
{
    return state_ != GameObjectState::DEAD && !map.canSee(this);
}

} // end of namespace botlib
} // end of namespace mcdane

