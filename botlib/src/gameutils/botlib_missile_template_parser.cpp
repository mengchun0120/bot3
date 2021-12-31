#include <botlib_missile_template_parser.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

MissileTemplateParser::MissileTemplateParser(
            const NamedMap<ComponentTemplate>& componentTemplateLib)
    : CompositeObjectTemplateParser(componentTemplateLib)
    , params_{
        jsonParam(damage_, "damage", true, gt(0.0f)),
        jsonParam(speed_, "speed", true, gt(0.0f))
      }
{
}

MissileTemplate* MissileTemplateParser::operator()(const rapidjson::Value& v)
{
    CompositeObjectTemplateParser::load(v);
    parse(params_, v);

    return new MissileTemplate(collideBreath_,
                               damage_,
                               speed_,
                               std::move(components_));
}

} // end of namespace botlib
} // end of namespace mcdane

