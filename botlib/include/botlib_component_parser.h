#ifndef INCLUDED_BOTLIB_COMPONENT_PARSER_H
#define INCLUDED_BOTLIB_COMPONENT_PARSER_H

#include <string>
#include <vector>
#include <rapidjson/document.h>
#include <commonlib_json_param.h>
#include <commonlib_named_map.h>
#include <botlib_component_template.h>
#include <botlib_component.h>

namespace mcdane {
namespace botlib {

class ComponentParser {
public:
    ComponentParser(
            const commonlib::NamedMap<ComponentTemplate>& componentLib);

    void initComponent(Component& c,
                       const rapidjson::Value& v);

private:
    const commonlib::NamedMap<ComponentTemplate>& componentLib_;
    std::string templateName_;
    commonlib::Vector2 pos_;
    commonlib::Vector2 direction_;
    std::vector<commonlib::JsonParamPtr> params_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

