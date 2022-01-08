#include <commonlib_exception.h>
#include <botlib_composite_object_template_parser.h>

using namespace mcdane::commonlib;

namespace mcdane {
namespace botlib {

CompositeObjectTemplateParser::CompositeObjectTemplateParser(
                            const ComponentTemplateLib& componentTemplateLib)
    : componentParser_(componentTemplateLib)
{
}

void CompositeObjectTemplateParser::load(const rapidjson::Value& v)
{
    GameObjectTemplateParser::load(v);

    const rapidjson::Value* a = findJson(v, {"components"});
    if (!a)
    {
        THROW_EXCEPT(ParseException, "Failed to find components");
    }

    if (!a->IsArray())
    {
        THROW_EXCEPT(ParseException, "components is not array");
    }

    if (a->Capacity() == 0)
    {
        THROW_EXCEPT(ParseException, "components is empty");
    }

    components_.resize(a->Capacity());
    for (unsigned int i = 0; i < a->Capacity(); ++i)
    {
        componentParser_.initComponent(components_[i], (*a)[i]);
    }
}

} // end of namespace botlib
} // end of namespace mcdane

