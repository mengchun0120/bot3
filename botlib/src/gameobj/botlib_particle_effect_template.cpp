#include <algorithm>
#include <botlib_constants.h>
#include <botlib_particle_effect_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

ParticleEffectTemplate::ParticleEffectTemplate(float acceleration1,
                                               float duration1,
                                               float particleSize1,
                                               const std::vector<Vector2>& startPos,
                                               const std::vector<Vector2>& direction,
                                               const std::vector<float>& initSpeed,
                                               const Texture* texture1,
                                               const Color& color1)
    : GameObjectTemplate(GameObjectType::EFFECT, 0.0f, 0.0f)
    , numParticles_(startPos.size() / Constants::FLOATS_PER_DIRECTION)
    , acceleration_(acceleration1)
    , particleSize_(particleSize1)
    , texture_(texture1)
    , color_(color1)
{
    loadVertexArray(startPos, direction, initSpeed);
    resetSpan(duration1, acceleration1, particleSize1, startPos,
              direction, initSpeed);
}

void ParticleEffectTemplate::loadVertexArray(const std::vector<Vector2>& startPos,
                                             const std::vector<Vector2>& direction,
                                             const std::vector<float>& initSpeed)
{
    vertexArray_.load({
        BufferBlock(startPos.data(), numParticles_, Constants::POS_SIZE, 0),
        BufferBlock(direction.data(), numParticles_, Constants::DIRECTION_SIZE, 0),
        BufferBlock(initSpeed.data(), numParticles_, sizeof(float), 0)
    });
}

void ParticleEffectTemplate::resetSpan(float duration1,
                                       float acceleration1,
                                       float particleSize1,
                                       const std::vector<Vector2>& startPos,
                                       const std::vector<Vector2>& direction,
                                       const std::vector<float>& initSpeed)
{
    span_ = 0.0f;
    for (int i = 0; i < numParticles_; ++i)
    {
        float s = calculateSpan(duration1, acceleration1, particleSize1,
                                startPos[i], direction[i], initSpeed[i]);
        if (s > span_)
        {
            span_ = s;
        }
    }
}

float ParticleEffectTemplate::calculateSpan(float duration1,
                                            float acceleration1,
                                            float particleSize1,
                                            const Vector2& startPos,
                                            const Vector2& direction,
                                            float initSpeed)
{
    Vector2 endPos = startPos + direction * (initSpeed * duration1 -
                     acceleration1 * duration1 * duration1 / 2.0);
    return std::max(endPos[0], endPos[1]) + particleSize1;
}

} // end of namespace botlib
} // end of namespace mcdane

