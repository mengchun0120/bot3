#ifndef INCLUDED_BOTLIB_MISSILE_TEMPLATE_PARSER_H
#define INCLUDED_BOTLIB_MISSILE_TEMPLATE_PARSER_H

#include <botlib_composite_object_template_parser.h>

namespace mcdane {
namespace botlib {

class MissileTemplateParser: public CompositeObjectTemplateParser {
public:
    MissileTemplateParser(
            const ComponentTemplateLib& componentTemplateLib,
            const ParticleEffectTemplateLib& particleEffectTemplateLib);

    MissileTemplate* operator()(const rapidjson::Value& v);

private:
    const ParticleEffectTemplateLib& particleEffectTemplateLib_;
    float damage_;
    float speed_;
    float explodeBreath_;
    std::string explodeEffectName_;
    std::vector<commonlib::JsonParamPtr> params_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

