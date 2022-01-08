#ifndef INCLUDED_BOTLIB_TILE_TEMPLATE_PARSER_H
#define INCLUDED_BOTLIB_TILE_TEMPLATE_PARSER_H

#include <botlib_composite_object_template_parser.h>

namespace mcdane {
namespace botlib {

class TileTemplate;

class TileTemplateParser: public CompositeObjectTemplateParser {
public:
    TileTemplateParser(
            const ComponentTemplateLib& componentTemplateLib);

    TileTemplate* operator()(const rapidjson::Value& v);

private:
    float hp_;
    std::vector<commonlib::JsonParamPtr> params_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

