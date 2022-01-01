#ifndef INCLUDED_BOTLIB_PARTICLE_EFFECT_TEMPLATE_H
#define INCLUDED_BOTLIB_PARTICLE_EFFECT_TEMPLATE_H

#include <commonlib_vertex_array.h>
#include <commonlib_texture.h>
#include <commonlib_color.h>
#include <commonlib_vector.h>
#include <botlib_game_object_template.h>

namespace mcdane {
namespace botlib {

class ParticleEffectTemplate: public GameObjectTemplate {
public:
    ParticleEffectTemplate(float acceleration1,
                           float duration1,
                           float particleSize1,
                           const std::vector<commonlib::Vector2>& startPos,
                           const std::vector<commonlib::Vector2>& direction,
                           const std::vector<float>& initSpeed,
                           const commonlib::Texture* texture1,
                           const commonlib::Color& color1);

    ~ParticleEffectTemplate() override = default;

    inline int numParticles() const;

    inline float acceleration() const;

    inline float duration() const;

    inline float particleSize() const;

    inline const commonlib::VertexArray& vertexArray() const;

    inline const commonlib::Texture* texture() const;

    inline const commonlib::Color& color() const;

protected:
    void loadVertexArray(const std::vector<commonlib::Vector2>& startPos,
                         const std::vector<commonlib::Vector2>& direction,
                         const std::vector<float>& initSpeed);

    void resetSpan(float duration1,
                   float acceleration1,
                   float particleSize1,
                   const std::vector<commonlib::Vector2>& startPos,
                   const std::vector<commonlib::Vector2>& direction,
                   const std::vector<float>& initSpeed);

    float calculateSpan(float duration1,
                        float acceleration1,
                        float particleSize1,
                        const commonlib::Vector2& startPos,
                        const commonlib::Vector2& direction,
                        float initSpeed);

protected:
    int numParticles_;
    float acceleration_;
    float initSpeed_;
    float duration_;
    float particleSize_;
    commonlib::VertexArray vertexArray_;
    const commonlib::Texture *texture_;
    const commonlib::Color color_;
};

int ParticleEffectTemplate::numParticles() const
{
    return numParticles_;
}

float ParticleEffectTemplate::acceleration() const
{
    return acceleration_;
}

float ParticleEffectTemplate::duration() const
{
    return duration_;
}

float ParticleEffectTemplate::particleSize() const
{
    return particleSize_;
}

const commonlib::VertexArray& ParticleEffectTemplate::vertexArray() const
{
    return vertexArray_;
}

const commonlib::Texture* ParticleEffectTemplate::texture() const
{
    return texture_;
}

const commonlib::Color& ParticleEffectTemplate::color() const
{
    return color_;
}

} // end of namespace botlib
} // end of namespace mcdane

#endif
