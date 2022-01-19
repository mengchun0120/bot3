#include <commonlib_log.h>
#include <botlib_graphics.h>
#include <botlib_game_map.h>
#include <botlib_particle_effect.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void ParticleEffect::init(const ParticleEffectTemplate* t,
                     const Vector2& pos)
{
    GameObject::init(t, pos);
    startTime_ = Clock::now();
    elapsedTime_ = 0.0f;
}

void ParticleEffect::present() const
{
    ParticleShaderProgram& shader = Graphics::particleShader();
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

void ParticleEffect::update(GameMap& map,
                            float delta)
{
    elapsedTime_ = elapsedTimeMs(startTime_);
    if (elapsedTime_ >= getTemplate()->duration())
    {
        setAlive(false);
    }
}

} // end of namespace botlib
} // end of namespace mcdane
