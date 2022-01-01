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
}

void ParticleEffect::present() const
{
    ParticleShaderProgram& shader = Graphics::particleShader();
    const ParticleEffectTemplate* t = getTemplate();

    shader.setRef(pos_);
    shader.setAcceleration(t->acceleration());
    shader.setParticleSize(t->particleSize());
    shader.setCurTime(timeDistMs(Clock::now(), startTime_));
    shader.setStartPosDirectionSpeed(t->vertexArray());
    shader.setTexture(t->texture()->id());
    shader.setColor(t->color());

    glDrawArrays(GL_POINTS, 0, t->numParticles());
}

void ParticleEffect::update(GameMap& map,
                            float delta)
{
    if (timeDistMs(Clock::now(), startTime_) >= getTemplate()->duration())
    {
        setAlive(false);
    }
}

} // end of namespace botlib
} // end of namespace mcdane

