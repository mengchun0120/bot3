#include <commonlib_exception.h>
#include <commonlib_file_utils.h>
#include <commonlib_vector.h>
#include <commonlib_named_map.h>
#include <commonlib_texture.h>
#include <botlib_particle_effect_template.h>
#include <botlib_particle_effect_template_parser.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

ParticleEffectTemplateParser::ParticleEffectTemplateParser(
                                        const std::string& libDir,
                                        const NamedMap<Texture>& textureLib)
    : libDir_(libDir)
    , textureLib_(textureLib)
    , params_{
        jsonParam(acceleration_, "acceleration", true, ge(0.0f)),
        jsonParam(duration_, "duration", true, gt(0.0f)),
        jsonParam(particleSize_, "particleSize", true, gt(0.0f)),
        jsonParam(startPosFile_, "startPosFile", true, k_nonEmptyStrV),
        jsonParam(directionFile_, "directionFile", true, k_nonEmptyStrV),
        jsonParam(initSpeedFile_, "initSpeedFile", true, k_nonEmptyStrV),
        jsonParam(textureName_, "texture", true, k_nonEmptyStrV),
        jsonParam(color_, "color")
      }
{
}

ParticleEffectTemplate* ParticleEffectTemplateParser::operator()(
                                           const rapidjson::Value& v)
{
    parse(params_, v);

    const Texture* texture = textureLib_.search(textureName_);
    if (!texture)
    {
        THROW_EXCEPT(ParseException, "Failed to find texture " + textureName_);
    }

    std::vector<Vector2> startPos;
    std::vector<Vector2> direction;
    std::vector<float> initSpeed;

    readList(startPos, constructPath({libDir_, startPosFile_}));
    readList(direction, constructPath({libDir_, directionFile_}));
    readList(initSpeed, constructPath({libDir_, initSpeedFile_}));

    return new ParticleEffectTemplate(acceleration_,
                                      duration_,
                                      particleSize_,
                                      startPos,
                                      direction,
                                      initSpeed,
                                      texture,
                                      color_);
}

} // end of namespace botlib
} // end of namespace mcdane

