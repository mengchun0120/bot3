#ifndef INCLUDED_BOTLIB_COMPONENT_PARSER_H
#define INCLUDED_BOTLIB_COMPONENT_PARSER_H

#include <string>
#include <vector>
#include <rapidjson/document.h>
#include <commonlib_json_param.h>
#include <botlib_typedef.h>

namespace mcdane {
namespace botlib {

class Component;

class ComponentParser {
public:
    ComponentParser(
            const ComponentTemplateLib& componentTemplateLib);

    void initComponent(Component& c,
                       const rapidjson::Value& v);

private:
    const ComponentTemplateLib& componentTemplateLib_;
    std::string templateName_;
    commonlib::Vector2 pos_;
    commonlib::Vector2 direction_;
    std::vector<commonlib::JsonParamPtr> params_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

