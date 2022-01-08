#ifndef INCLUDED_BOTLIB_COMPOSITE_OBJECT_TEMPLATE_PARSER_H
#define INCLUDED_BOTLIB_COMPOSITE_OBJECT_TEMPLATE_PARSER_H

#include <botlib_component_parser.h>
#include <botlib_component.h>
#include <botlib_game_object_template_parser.h>

namespace mcdane {
namespace botlib {

class CompositeObjectTemplateParser: public GameObjectTemplateParser {
public:
    CompositeObjectTemplateParser(
            const ComponentTemplateLib& componentTemplateLib);

    void load(const rapidjson::Value& v);

protected:
    ComponentParser componentParser_;
    std::vector<Component> components_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

