#include <botlib_constants.h>
#include <botlib_particle_effect_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

ParticleEffectTemplate::ParticleEffectTemplate(float span1,
                                               float acceleration1,
                                               float initSpeed1,
                                               float duration1,
                                               float particleSize1,
                                               const std::vector<Vector2>& startPos,
                                               const std::vector<Vector2>& direction,
                                               const std::vector<float>& initSpeed,
                                               const Texture* texture1,
                                               const Color* color1)
    : GameObjectTemplate(GameObjectType::EFFECT, span1, 0.0f)
    , numParticles_(startPos.size() / Constants::FLOATS_PER_DIRECTION)
    , acceleration_(acceleration1)
    , initSpeed_(initSpeed1)
    , particleSize_(particleSize1)
    , texture_(texture1)
    , color_(color1)
{
    vertexArray_.load({
        BufferBlock(startPos.data(), numParticles_, Constants::POS_SIZE, 0),
        BufferBlock(direction.data(), numParticles_, Constants::DIRECTION_SIZE, 0),
        BufferBlock(initSpeed.data(), numParticles_, sizeof(float), 0)
    });
}

} // end of namespace botlib
} // end of namespace mcdane

