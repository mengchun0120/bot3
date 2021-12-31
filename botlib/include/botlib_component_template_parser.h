#ifndef INCLUDED_BOTLIB_COMPONENT_TEMPLATE_PARSER_H
#define INCLUDED_BOTLIB_COMPONENT_TEMPLATE_PARSER_H

#include <string>
#include <vector>
#include <rapidjson/document.h>
#include <commonlib_json_param.h>
#include <commonlib_named_map.h>
#include <commonlib_texture.h>
#include <botlib_rectangle.h>
#include <botlib_component_template.h>

namespace mcdane {
namespace botlib {

class ComponentTemplateParser {
public:
    ComponentTemplateParser(
            const commonlib::NamedMap<commonlib::Texture>& textureLib,
            const commonlib::NamedMap<Rectangle>& rectLib);

    ComponentTemplate* operator()(const rapidjson::Value& v);

private:
    const commonlib::NamedMap<commonlib::Texture>& textureLib_;
    const commonlib::NamedMap<Rectangle>& rectLib_;
    std::string textureName_;
    std::string rectName_;
    std::vector<commonlib::JsonParamPtr> params_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

