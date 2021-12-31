#include <commonlib_exception.h>
#include <botlib_component_parser.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

ComponentParser::ComponentParser(
        const NamedMap<ComponentTemplate>& componentLib)
    : componentLib_(componentLib)
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

    ComponentTemplate* t = componentLib_.search(templateName_);
    if (!t)
    {
        THROW_EXCEPT(ParseException,
                     "Failed to find ComponentTemplate " + templateName_);
    }

    c.init(t, pos_, direction_);
}

} // end of namespace botlib
} // end of namespace mcdane

