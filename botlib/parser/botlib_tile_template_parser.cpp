#include <commonlib_log.h>
#include <botlib_tile_template.h>
#include <botlib_tile_template_parser.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

TileTemplateParser::TileTemplateParser(
                        const ComponentTemplateLib& componentTemplateLib)
    : CompositeObjectTemplateParser(componentTemplateLib)
    , params_{
        jsonParam(hp_, "hp", true, ge(0.0f))
      }
{
}

TileTemplate* TileTemplateParser::operator()(const rapidjson::Value& v)
{
    load(v);
    parse(params_, v);

    return new TileTemplate(collideBreath_,
                            hp_,
                            invincible_,
                            std::move(components_));
}

} // end of namespace botlib
} // end of namespace mcdane

