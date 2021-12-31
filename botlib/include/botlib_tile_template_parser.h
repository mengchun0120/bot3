#ifndef INCLUDED_BOTLIB_TILE_TEMPLATE_PARSER_H
#define INCLUDED_BOTLIB_TILE_TEMPLATE_PARSER_H

#include <botlib_composite_object_template_parser.h>
#include <botlib_tile_template.h>

namespace mcdane {
namespace botlib {

class TileTemplateParser: public CompositeObjectTemplateParser {
public:
    TileTemplateParser(
            const commonlib::NamedMap<ComponentTemplate>& componentTemplateLib);

    TileTemplate* operator()(const rapidjson::Value& v);

private:
    float hp_;
    std::vector<commonlib::JsonParamPtr> params_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

