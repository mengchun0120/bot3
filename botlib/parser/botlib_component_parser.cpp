#include <commonlib_exception.h>
#include <commonlib_named_map.h>
#include <botlib_component_template.h>
#include <botlib_component.h>
#include <botlib_component_parser.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

ComponentParser::ComponentParser(
        const ComponentTemplateLib& componentTemplateLib)
    : componentTemplateLib_(componentTemplateLib)
    , params_{
        jsonParam(templateName_, "template", true, k_nonEmptyStrV),
        jsonParam(pos_, "pos"),
        jsonParam(direction_, "direction")
      }
{
}

void ComponentParser::initComponent(Component& c,
                                    const rapidjson::Value& v)
{
    parse(params_, v);

    ComponentTemplate* t = componentTemplateLib_.search(templateName_);
    if (!t)
    {
        THROW_EXCEPT(ParseException,
                     "Failed to find ComponentTemplate " + templateName_);
    }

    c.init(t, pos_, direction_);
}

} // end of namespace botlib
} // end of namespace mcdane

