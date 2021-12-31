#ifndef INCLUDED_BOTLIB_MISSILE_TEMPLATE_PARSER_H
#define INCLUDED_BOTLIB_MISSILE_TEMPLATE_PARSER_H

#include <botlib_composite_object_template_parser.h>
#include <botlib_missile_template.h>

namespace mcdane {
namespace botlib {

class MissileTemplateParser: public CompositeObjectTemplateParser {
public:
    MissileTemplateParser(
            const commonlib::NamedMap<ComponentTemplate>& componentTemplateLib);

    MissileTemplate* operator()(const rapidjson::Value& v);

private:
    float damage_;
    float speed_;
    std::vector<commonlib::JsonParamPtr> params_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

