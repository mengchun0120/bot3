#ifndef INCLUDED_BOTLIB_PARTICLE_EFFECT_TEMPLATE_PARSER_H
#define INCLUDED_BOTLIB_PARTICLE_EFFECT_TEMPLATE_PARSER_H

#include <vector>
#include <string>
#include <rapidjson/document.h>
#include <commonlib_json_param.h>
#include <commonlib_color.h>
#include <botlib_typedef.h>

namespace mcdane {
namespace botlib {

class ParticleEffectTemplateParser {
public:
    ParticleEffectTemplateParser(const TextureLib& textureLib);

    ParticleEffectTemplate* operator()(const rapidjson::Value& v);

private:
    const TextureLib& textureLib_;
    float acceleration_;
    float duration_;
    float particleSize_;
    std::string startPosFile_;
    std::string directionFile_;
    std::string initSpeedFile_;
    std::string textureName_;
    commonlib::Color color_;
    std::vector<commonlib::JsonParamPtr> params_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

