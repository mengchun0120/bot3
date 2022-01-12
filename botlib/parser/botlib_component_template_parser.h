#ifndef INCLUDED_BOTLIB_COMPONENT_TEMPLATE_PARSER_H
#define INCLUDED_BOTLIB_COMPONENT_TEMPLATE_PARSER_H

#include <string>
#include <vector>
#include <rapidjson/document.h>
#include <commonlib_json_param.h>
#include <botlib_typedef.h>

namespace mcdane {
namespace botlib {

class ComponentTemplateParser {
public:
    ComponentTemplateParser(
            const TextureLib& textureLib,
            const RectLib& rectLib);

    ComponentTemplate* operator()(const rapidjson::Value& v);

private:
    const TextureLib& textureLib_;
    const RectLib& rectLib_;
    std::string textureName_;
    std::string rectName_;
    std::vector<commonlib::JsonParamPtr> params_;
};

} // end of namespace botlib
} // end of namespace mcdane

#endif

