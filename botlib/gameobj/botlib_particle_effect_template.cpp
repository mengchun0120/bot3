#include <algorithm>
#include <commonlib_log.h>
#include <commonlib_json_utils.h>
#include <commonlib_json_param.h>
#include <commonlib_file_utils.h>
#include <commonlib_named_map.h>
#include <commonlib_texture.h>
#include <botlib_constants.h>
#include <botlib_particle_effect_template.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

void ParticleEffectTemplate::init(const std::string &name,
                                  const rapidjson::Value &v,
                                  const TextureLib &textureLib,
                                  const std::string &libDir)
{
    std::string startPosFile, directionFile, initSpeedFile, textureName;
    std::vector<JsonParamPtr> params{
        jsonParam(acceleration_, "acceleration", true, ge(0.0f)),
        jsonParam(duration_, "duration", true, gt(0.0f)),
        jsonParam(particleSize_, "particleSize", true, gt(0.0f)),
        jsonParam(startPosFile, "startPosFile", true, k_nonEmptyStrV),
        jsonParam(directionFile, "directionFile", true, k_nonEmptyStrV),
        jsonParam(initSpeedFile, "initSpeedFile", true, k_nonEmptyStrV),
        jsonParam(textureName, "texture", true, k_nonEmptyStrV),
        jsonParam(color_, "color")
    };

    parse(params, v);

    texture_ = textureLib.search(textureName);
    if (!texture_)
    {
        THROW_EXCEPT(ParseException, "Failed to find texture " + textureName);
    }

    std::vector<Vector2> startPos, direction;
    std::vector<float> initSpeed;

    loadVertexData(startPos, direction, initSpeed,
                   startPosFile, directionFile, initSpeedFile, libDir);
    loadVertexArray(startPos, direction, initSpeed);
    resetSpan(startPos, direction, initSpeed);

    GameObjectTemplate::init(GameObjectType::EFFECT, name, v);
}


void ParticleEffectTemplate::loadVertexData(
                                std::vector<commonlib::Vector2> &startPos,
                                std::vector<commonlib::Vector2> &direction,
                                std::vector<float> &initSpeed,
                                const std::string &startPosFile,
                                const std::string &directionFile,
                                const std::string &initSpeedFile,
                                const std::string &dataDir)
{
    readList(startPos, constructPath({dataDir, startPosFile}));
    readList(direction, constructPath({dataDir, directionFile}));
    readList(initSpeed, constructPath({dataDir, initSpeedFile}));

    if (startPos.empty())
    {
        THROW_EXCEPT(InvalidArgumentException, "startPos is empty");
    }

    if (startPos.size() != direction.size())
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "startPos's size doesn't match direciton's size");
    }

    if (startPos.size() != initSpeed.size())
    {
        THROW_EXCEPT(InvalidArgumentException,
                     "startPos's size doesn't match initSpeed's size");
    }

    numParticles_ = startPos.size();
}

void ParticleEffectTemplate::loadVertexArray(const std::vector<Vector2> &startPos,
                                             const std::vector<Vector2> &direction,
                                             const std::vector<float> &initSpeed)
{
    vertexArray_.init({
        BufferBlock(startPos.data(), numParticles_, Constants::POS_SIZE, 0),
        BufferBlock(direction.data(), numParticles_, Constants::DIRECTION_SIZE, 0),
        BufferBlock(initSpeed.data(), numParticles_, sizeof(float), 0)
    });
}

void ParticleEffectTemplate::resetSpan(const std::vector<Vector2> &startPos,
                                       const std::vector<Vector2> &direction,
                                       const std::vector<float> &initSpeed)
{
    span_ = 0.0f;
    for (int i = 0; i < numParticles_; ++i)
    {
        float s = calculateSpan(startPos[i], direction[i], initSpeed[i]);
        if (s > span_)
        {
            span_ = s;
        }
    }
}

float ParticleEffectTemplate::calculateSpan(const Vector2 &startPos,
                                            const Vector2 &direction,
                                            float initSpeed)
{
    Vector2 endPos = startPos + direction * (initSpeed * duration_ -
                     acceleration_ * duration_ * duration_ / 2.0);
    return std::max(endPos[0], endPos[1]) + particleSize_;
}

} // end of namespace botlib
} // end of namespace mcdane

