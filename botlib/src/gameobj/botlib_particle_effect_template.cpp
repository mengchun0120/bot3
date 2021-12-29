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
                                               const std::vector<Vector2>& directions,
                                               const Texture* texture1,
                                               const Color* color1)
    : GameObjectTemplate(GameObjectType::EFFECT, span1, 0.0f)
    , numParticles_(directions.size() / Constants::FLOATS_PER_DIRECTION)
    , acceleration_(acceleration1)
    , initSpeed_(initSpeed1)
    , particleSize_(particleSize1)
    , texture_(texture1)
    , color_(color1)
{
    directionVertexArray_.load(directions.data(),
                               numParticles_,
                               Constants::DIRECTION_SIZE);
}

} // end of namespace botlib
} // end of namespace mcdane

